#include "Game.h"
#include <algorithm>
#include <thread>
#include <iostream>

namespace Tetris {

// Static factory functions
std::unique_ptr<TetrisGame> createStandardGame() {
    return std::make_unique<TetrisGame>();
}

std::unique_ptr<TetrisGame> createCustomGame(const TetrisGame::Config& config) {
    return std::make_unique<TetrisGame>(config);
}

// Constructor implementations
TetrisGame::TetrisGame() : TetrisGame(Config{}) {}

TetrisGame::TetrisGame(const Config& config) 
    : config_(config)
    , state_(GameState::MENU)
    , board_()
    , input_system_(config.input_config)
    , render_system_(config.render_config)
    , can_hold_(true)
    , score_(0)
    , level_(1)
    , total_lines_cleared_(0)
    , lines_cleared_this_level_(0)
    , rng_()
    , total_pieces_generated_(0)
    , stats_()
{
    initializeRNG();
    current_drop_speed_ = config_.difficulty.getDropSpeed(level_);
}

TetrisGame::~TetrisGame() {
    shutdown();
}

bool TetrisGame::initialize() {
    if (!input_system_.isReady() || !render_system_.isReady()) {
        return false;
    }
    
    resetGameState();
    
    // Set up board callback
    board_.setLineClearCallback([this](int lines, int /*level*/) {
        updateScore(lines);
    });
    
    return true;
}

void TetrisGame::shutdown() {
    // RAII handles cleanup automatically
}

int TetrisGame::run() {
    if (!initialize()) {
        return 1;
    }
    
    auto& renderer = render_system_.getRenderer();
    auto& input = input_system_.getHandler();
    
    auto last_frame_time = std::chrono::steady_clock::now();
    const auto target_frame_time = getTargetFrameTime();
    
    int menu_selection = 0;
    
    while (isRunning()) {
        auto current_time = std::chrono::steady_clock::now();
        auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            current_time - last_frame_time
        );
        last_frame_time = current_time;
        
        // Handle input
        InputState input_state = input.pollInput();
        handleInput(input_state);
        
        // Update game state
        switch (state_) {
            case GameState::MENU:
                if (input_state.action == InputAction::MOVE_DOWN) {
                    menu_selection = (menu_selection + 1) % 3;
                } else if (input_state.action == InputAction::ROTATE_CW) {
                    menu_selection = (menu_selection + 2) % 3;
                } else if (input_state.action == InputAction::HARD_DROP || 
                          input_state.action == InputAction::ROTATE_CW) {
                    switch (menu_selection) {
                        case 0: startNewGame(); break;
                        case 1: state_ = GameState::HELP; break;
                        case 2: state_ = GameState::EXITING; break;
                    }
                }
                renderer.renderMenu(menu_selection);
                break;
                
            case GameState::PLAYING:
                update(delta_time);
                render();
                break;
                
            case GameState::PAUSED:
                renderer.renderPause();
                break;
                
            case GameState::GAME_OVER:
                renderer.renderGameOver(score_, level_);
                break;
                
            case GameState::HELP:
                renderer.renderHelp();
                if (input_state.isValid()) {
                    state_ = GameState::MENU;
                }
                break;
                
            case GameState::EXITING:
                break;
        }
        
        // Frame rate limiting
        auto frame_time = std::chrono::steady_clock::now() - current_time;
        if (frame_time < target_frame_time) {
            std::this_thread::sleep_for(target_frame_time - frame_time);
        }
    }
    
    return 0;
}

void TetrisGame::startNewGame() {
    resetGameState();
    state_ = GameState::PLAYING;
    game_start_time_ = std::chrono::steady_clock::now();
    last_drop_time_ = game_start_time_;
    
    generateNextPiece();
    spawnNextPiece();
    generateNextPiece();
}

void TetrisGame::togglePause() {
    if (state_ == GameState::PLAYING) {
        state_ = GameState::PAUSED;
    } else if (state_ == GameState::PAUSED) {
        state_ = GameState::PLAYING;
    }
}

void TetrisGame::update(std::chrono::milliseconds delta_time) {
    if (state_ != GameState::PLAYING) return;
    
    updateGameplay(delta_time);
    updateStats();
}

void TetrisGame::render() {
    if (state_ != GameState::PLAYING) return;
    
    GameStats stats = getGameStatsForRender();
    render_system_.getRenderer().render(board_, current_piece_, stats);
}

void TetrisGame::handleInput(const InputState& input) {
    if (!input.isValid()) return;
    
    switch (state_) {
        case GameState::MENU:
            handleMenuInput(input);
            break;
        case GameState::PLAYING:
            // Handle game actions
            switch (input.action) {
                case InputAction::MOVE_LEFT:
                    movePiece({-1, 0});
                    break;
                case InputAction::MOVE_RIGHT:
                    movePiece({1, 0});
                    break;
                case InputAction::SOFT_DROP:
                    softDropPiece();
                    break;
                case InputAction::HARD_DROP:
                    hardDropPiece();
                    break;
                case InputAction::ROTATE_CW:
                    rotatePiece(true);
                    break;
                case InputAction::ROTATE_CCW:
                    rotatePiece(false);
                    break;
                case InputAction::HOLD:
                    holdPiece();
                    break;
                case InputAction::PAUSE:
                    togglePause();
                    break;
                case InputAction::QUIT:
                    state_ = GameState::EXITING;
                    break;
                default:
                    break;
            }
            break;
        case GameState::PAUSED:
            handlePauseInput(input);
            break;
        case GameState::GAME_OVER:
            handleGameOverInput(input);
            break;
        default:
            break;
    }
}

void TetrisGame::updateGameplay(std::chrono::milliseconds /*delta_time*/) {
    // Automatic piece dropping
    if (shouldDropPiece()) {
        if (!softDropPiece()) {
            lockPiece();
        }
        last_drop_time_ = std::chrono::steady_clock::now();
    }
    
    // Check for game over
    if (checkGameOver()) {
        state_ = GameState::GAME_OVER;
        if (game_over_callback_) {
            game_over_callback_(score_, level_);
        }
    }
}

void TetrisGame::handleMenuInput(const InputState& /*input*/) {
    // Handled in main run loop
}

void TetrisGame::handlePauseInput(const InputState& input) {
    if (input.action == InputAction::PAUSE) {
        togglePause();
    } else if (input.action == InputAction::QUIT) {
        state_ = GameState::EXITING;
    }
}

void TetrisGame::handleGameOverInput(const InputState& input) {
    if (input.action == InputAction::RESTART) {
        startNewGame();
    } else if (input.action == InputAction::QUIT) {
        state_ = GameState::EXITING;
    }
}

bool TetrisGame::movePiece(const Position& direction) {
    Position new_pos = current_piece_.getPosition() + direction;
    if (board_.canPlacePiece(current_piece_, new_pos, current_piece_.getRotation())) {
        current_piece_.setPosition(new_pos);
        return true;
    }
    return false;
}

bool TetrisGame::rotatePiece(bool clockwise) {
    Rotation new_rotation = current_piece_.getRotation();
    if (clockwise) {
        new_rotation = static_cast<Rotation>((static_cast<int>(new_rotation) + 1) % 4);
    } else {
        new_rotation = static_cast<Rotation>((static_cast<int>(new_rotation) + 3) % 4);
    }
    
    // Try simple rotation first
    if (board_.canPlacePiece(current_piece_, current_piece_.getPosition(), new_rotation)) {
        if (clockwise) {
            current_piece_.rotateClockwise();
        } else {
            current_piece_.rotateCounterClockwise();
        }
        return true;
    }
    
    // Try wall kicks (simplified SRS)
    std::vector<Position> kick_offsets = {{-1, 0}, {1, 0}, {0, -1}, {-1, -1}, {1, -1}};
    for (const auto& offset : kick_offsets) {
        Position test_pos = current_piece_.getPosition() + offset;
        if (board_.canPlacePiece(current_piece_, test_pos, new_rotation)) {
            current_piece_.setPosition(test_pos);
            if (clockwise) {
                current_piece_.rotateClockwise();
            } else {
                current_piece_.rotateCounterClockwise();
            }
            return true;
        }
    }
    
    return false;
}

int TetrisGame::hardDropPiece() {
    Position drop_pos = board_.findDropPosition(current_piece_);
    int drop_distance = drop_pos.y - current_piece_.getPosition().y;
    current_piece_.setPosition(drop_pos);
    
    // Add hard drop points
    score_ += drop_distance * config_.score_config.hard_drop;
    if (score_update_callback_) {
        score_update_callback_(score_, 0);
    }
    
    lockPiece();
    return drop_distance;
}

bool TetrisGame::softDropPiece() {
    if (movePiece({0, 1})) {
        score_ += config_.score_config.soft_drop;
        if (score_update_callback_) {
            score_update_callback_(score_, 0);
        }
        return true;
    }
    return false;
}

bool TetrisGame::holdPiece() {
    if (!can_hold_ || !config_.enable_hold) {
        return false;
    }
    
    if (held_piece_.isValid()) {
        // Swap current and held pieces
        std::swap(current_piece_, held_piece_);
        current_piece_.setPosition({Board::SPAWN_X, Board::SPAWN_Y});
        // Reset rotation to NORTH by creating a new piece with same type
        current_piece_ = createTetromino(current_piece_.getType(), {Board::SPAWN_X, Board::SPAWN_Y});
    } else {
        // Move current to held and spawn next
        held_piece_ = current_piece_;
        held_piece_.setPosition({0, 0});
        spawnNextPiece();
        generateNextPiece();
    }
    
    can_hold_ = false;
    return true;
}

void TetrisGame::lockPiece() {
    board_.placePiece(current_piece_);
    
    int lines_cleared = board_.clearLines();
    if (lines_cleared > 0) {
        total_lines_cleared_ += lines_cleared;
        lines_cleared_this_level_ += lines_cleared;
        
        updateScore(lines_cleared);
        updateLevel();
        
        if (lines_cleared == 4) {
            stats_.tetris_count++;
        }
    }
    
    can_hold_ = true;
    
    if (!spawnNextPiece()) {
        state_ = GameState::GAME_OVER;
        return;
    }
    
    generateNextPiece();
}

bool TetrisGame::spawnNextPiece() {
    current_piece_ = next_piece_;
    current_piece_.setPosition({Board::SPAWN_X, Board::SPAWN_Y});
    
    if (!board_.canPlacePiece(current_piece_)) {
        return false; // Game over
    }
    
    total_pieces_generated_++;
    stats_.total_pieces++;
    
    if (static_cast<size_t>(current_piece_.getType()) < stats_.piece_counts.size()) {
        stats_.piece_counts[static_cast<size_t>(current_piece_.getType())]++;
    }
    
    return true;
}

void TetrisGame::generateNextPiece() {
    if (config_.enable_7_bag) {
        if (piece_bag_.empty()) {
            fillPieceBag();
        }
        next_piece_ = createTetromino(piece_bag_.front(), {0, 0});
        piece_bag_.pop();
    } else {
        next_piece_ = createRandomTetromino({0, 0});
    }
}

void TetrisGame::fillPieceBag() {
    std::vector<TetrominoType> pieces = {
        TetrominoType::I, TetrominoType::O, TetrominoType::T, TetrominoType::S,
        TetrominoType::Z, TetrominoType::J, TetrominoType::L
    };
    
    std::shuffle(pieces.begin(), pieces.end(), rng_);
    
    for (auto piece : pieces) {
        piece_bag_.push(piece);
    }
}

void TetrisGame::updateScore(int lines_cleared) {
    int line_score = config_.score_config.calculateLineScore(lines_cleared, level_);
    score_ += line_score;
    
    if (score_update_callback_) {
        score_update_callback_(score_, lines_cleared);
    }
}

void TetrisGame::updateLevel() {
    int new_level = 1 + (total_lines_cleared_ / config_.difficulty.lines_per_level);
    if (new_level > level_ && new_level <= config_.difficulty.max_level) {
        level_ = new_level;
        updateDropSpeed();
        lines_cleared_this_level_ = 0;
        
        if (level_up_callback_) {
            level_up_callback_(level_);
        }
    }
}

void TetrisGame::updateDropSpeed() {
    current_drop_speed_ = config_.difficulty.getDropSpeed(level_);
}

bool TetrisGame::shouldDropPiece() const {
    auto current_time = std::chrono::steady_clock::now();
    auto time_since_drop = std::chrono::duration_cast<std::chrono::milliseconds>(
        current_time - last_drop_time_
    );
    return time_since_drop >= current_drop_speed_;
}

void TetrisGame::resetGameState() {
    board_.reset();
    score_ = 0;
    level_ = 1;
    total_lines_cleared_ = 0;
    lines_cleared_this_level_ = 0;
    can_hold_ = true;
    total_pieces_generated_ = 0;
    
    current_piece_.reset();
    next_piece_.reset();
    held_piece_.reset();
    
    // Clear piece bag
    while (!piece_bag_.empty()) {
        piece_bag_.pop();
    }
    
    updateDropSpeed();
    
    // Reset stats
    stats_ = DetailedStats{};
    stats_.game_start_time = std::chrono::steady_clock::now();
}

void TetrisGame::updateStats() {
    auto current_time = std::chrono::steady_clock::now();
    stats_.total_play_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        current_time - stats_.game_start_time
    );
    
    stats_.score = score_;
    stats_.level = level_;
    stats_.lines_cleared = total_lines_cleared_;
    
    if (stats_.total_play_time.count() > 0) {
        stats_.pieces_per_second = static_cast<double>(stats_.total_pieces) / 
                                  (stats_.total_play_time.count() / 1000.0);
    }
}

GameStats TetrisGame::getGameStatsForRender() const {
    GameStats stats;
    stats.score = score_;
    stats.level = level_;
    stats.lines_cleared = total_lines_cleared_;
    stats.total_pieces = stats_.total_pieces;
    stats.next_piece = next_piece_.getType();
    stats.held_piece = held_piece_.getType();
    stats.can_hold = can_hold_;
    return stats;
}

bool TetrisGame::checkGameOver() {
    return board_.isGameOver();
}

void TetrisGame::initializeRNG() {
    std::random_device rd;
    rng_.seed(rd());
}

TetrisGame::DetailedStats TetrisGame::getDetailedStats() const {
    return stats_;
}

} // namespace Tetris
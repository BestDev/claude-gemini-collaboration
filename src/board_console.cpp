#include "board.h"
#include <algorithm>
#include <iostream>

namespace tetris {

Board::Board() noexcept 
    : state_(GameState::PLAYING), hold_used_(false), score_(0), level_(1), lines_cleared_(0) {
    clearGrid();
}

void Board::initialize() noexcept {
    clearGrid();
    state_ = GameState::PLAYING;
    hold_used_ = false;
    score_ = 0;
    level_ = 1;
    lines_cleared_ = 0;
    
    current_piece_.reset();
    next_piece_.reset();
    hold_piece_.reset();
    
    spawnNewPiece();
}

void Board::reset() noexcept {
    initialize();
}

bool Board::spawnNewPiece() noexcept {
    if (!next_piece_) {
        next_piece_.reset(new Piece(Piece::generateRandomType(), Position(SPAWN_X, SPAWN_Y)));
    }
    
    current_piece_ = std::move(next_piece_);
    next_piece_.reset(new Piece(Piece::generateRandomType(), Position(SPAWN_X, SPAWN_Y)));
    
    if (!isValidPosition(*current_piece_)) {
        state_ = GameState::GAME_OVER;
        triggerEvent(GameEvent::GAME_OVER);
        return false;
    }
    
    hold_used_ = false;
    triggerEvent(GameEvent::PIECE_SPAWNED);
    return true;
}

bool Board::moveCurrentPieceLeft() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveLeft();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveLeft();
        return true;
    }
    return false;
}

bool Board::moveCurrentPieceRight() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveRight();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveRight();
        return true;
    }
    return false;
}

bool Board::moveCurrentPieceDown() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveDown();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveDown();
        addScore(SCORE_SOFT_DROP);
        return true;
    }
    return false;
}

bool Board::rotateCurrentPiece(RotationDirection direction) noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.rotate(direction);
    
    Piece kicked_piece = tryWallKick(test_piece, direction);
    
    if (isValidPosition(kicked_piece)) {
        *current_piece_ = kicked_piece;
        return true;
    }
    return false;
}

int Board::hardDropCurrentPiece() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return 0;
    
    int drop_distance = 0;
    while (moveCurrentPieceDown()) {
        drop_distance++;
    }
    
    addScore(drop_distance * SCORE_HARD_DROP);
    return drop_distance;
}

bool Board::holdCurrentPiece() noexcept {
    if (!current_piece_ || hold_used_ || state_ != GameState::PLAYING) return false;
    
    if (!hold_piece_) {
        hold_piece_ = std::move(current_piece_);
        hold_piece_->setPosition(Position(0, 0));
        spawnNewPiece();
    } else {
        std::swap(current_piece_, hold_piece_);
        current_piece_->setPosition(Position(SPAWN_X, SPAWN_Y));
        
        if (!isValidPosition(*current_piece_)) {
            return false;
        }
    }
    
    hold_used_ = true;
    return true;
}

bool Board::isValidPosition(const Piece& piece) const noexcept {
    auto positions = piece.getBlockPositions();
    
    for (const auto& pos : positions) {
        if (pos.x < 0 || pos.x >= BOARD_WIDTH || pos.y >= BOARD_HEIGHT) {
            return false;
        }
        
        if (pos.y < 0) continue;
        
        if (grid_[pos.y][pos.x] != PieceType::EMPTY) {
            return false;
        }
    }
    
    return true;
}

bool Board::canPlacePieceAt(const Piece& piece, const Position& pos) const noexcept {
    Piece test_piece = piece;
    test_piece.setPosition(pos);
    return isValidPosition(test_piece);
}

bool Board::isCurrentPieceLanded() const noexcept {
    if (!current_piece_) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveDown();
    
    return !isValidPosition(test_piece);
}

void Board::lockCurrentPiece() noexcept {
    if (!current_piece_) return;
    
    auto positions = current_piece_->getBlockPositions();
    for (const auto& pos : positions) {
        if (pos.y >= 0 && pos.y < BOARD_HEIGHT && pos.x >= 0 && pos.x < BOARD_WIDTH) {
            grid_[pos.y][pos.x] = current_piece_->getType();
        }
    }
    
    triggerEvent(GameEvent::PIECE_LANDED);
    
    int cleared = clearCompletedLines();
    if (cleared > 0) {
        triggerEvent(GameEvent::LINE_CLEARED, cleared);
    }
    
    spawnNewPiece();
}

int Board::clearCompletedLines() noexcept {
    int lines_cleared = 0;
    
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        if (isLineComplete(row)) {
            removeLine(row);
            lines_cleared++;
            row++;
        }
    }
    
    if (lines_cleared > 0) {
        lines_cleared_ += lines_cleared;
        
        int points = 0;
        switch (lines_cleared) {
            case 1: points = SCORE_SINGLE * level_; break;
            case 2: points = SCORE_DOUBLE * level_; break;
            case 3: points = SCORE_TRIPLE * level_; break;
            case 4: points = SCORE_TETRIS * level_; break;
        }
        addScore(points);
        
        updateLevel();
    }
    
    return lines_cleared;
}

bool Board::isLineComplete(int row) const noexcept {
    if (row < 0 || row >= BOARD_HEIGHT) return false;
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        if (grid_[row][col] == PieceType::EMPTY) {
            return false;
        }
    }
    return true;
}

void Board::removeLine(int row) noexcept {
    if (row < 0 || row >= BOARD_HEIGHT) return;
    
    for (int r = row; r > 0; r--) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            grid_[r][col] = grid_[r - 1][col];
        }
    }
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        grid_[0][col] = PieceType::EMPTY;
    }
}

PieceType Board::getCellType(int x, int y) const noexcept {
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return PieceType::EMPTY;
    }
    return grid_[y][x];
}

void Board::addScore(unsigned long points) noexcept {
    score_ += points;
}

int Board::getDropInterval() const noexcept {
    int base_interval = 1000;
    int level_speedup = (level_ - 1) * 50;
    return std::max(100, base_interval - level_speedup);
}

Piece Board::calculateGhostPiece() const noexcept {
    if (!current_piece_) {
        return Piece();
    }
    
    Piece ghost = *current_piece_;
    
    while (true) {
        Piece test_piece = ghost;
        test_piece.moveDown();
        
        if (!isValidPosition(test_piece)) {
            break;
        }
        ghost.moveDown();
    }
    
    return ghost;
}

bool Board::isGameOver() const noexcept {
    return state_ == GameState::GAME_OVER;
}

int Board::getBoardHeight() const noexcept {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (grid_[row][col] != PieceType::EMPTY) {
                return BOARD_HEIGHT - row;
            }
        }
    }
    return 0;
}

int Board::countHoles() const noexcept {
    int holes = 0;
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        bool found_block = false;
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            if (grid_[row][col] != PieceType::EMPTY) {
                found_block = true;
            } else if (found_block) {
                holes++;
            }
        }
    }
    
    return holes;
}

// ncurses 의존적인 함수들은 빈 구현으로 대체
void Board::draw(int start_x, int start_y, bool show_ghost) const noexcept {
    // 콘솔 버전에서는 별도 렌더러 사용
}

void Board::drawNextPiece(int start_x, int start_y) const noexcept {
    // 콘솔 버전에서는 별도 렌더러 사용
}

void Board::drawHoldPiece(int start_x, int start_y) const noexcept {
    // 콘솔 버전에서는 별도 렌더러 사용
}

void Board::drawGameInfo(int start_x, int start_y) const noexcept {
    // 콘솔 버전에서는 별도 렌더러 사용
}

void Board::clearGrid() noexcept {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            grid_[row][col] = PieceType::EMPTY;
        }
    }
}

void Board::updateLevel() noexcept {
    int new_level = (lines_cleared_ / 10) + 1;
    if (new_level > level_) {
        level_ = new_level;
        triggerEvent(GameEvent::LEVEL_UP, level_);
    }
}

void Board::triggerEvent(GameEvent event, int value) noexcept {
    if (event_callback_) {
        event_callback_(event, value);
    }
}

Piece Board::tryWallKick(const Piece& piece, RotationDirection direction) const noexcept {
    std::vector<Position> kick_tests = {
        {0, 0},
        {-1, 0},
        {1, 0},
        {0, -1},
        {-1, -1},
        {1, -1}
    };
    
    for (const auto& kick : kick_tests) {
        Piece test_piece = piece;
        test_piece.move(kick);
        
        if (isValidPosition(test_piece)) {
            return test_piece;
        }
    }
    
    Piece original = piece;
    original.rotate(direction == RotationDirection::CLOCKWISE ? 
                   RotationDirection::COUNTERCLOCKWISE : RotationDirection::CLOCKWISE);
    return original;
}

void Board::drawCell(int x, int y, PieceType type, bool is_ghost) const noexcept {
    // 콘솔 버전에서는 사용하지 않음
}

} // namespace tetris
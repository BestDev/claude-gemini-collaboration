#pragma once

#include "Board.h"
#include "Tetromino.h"
#include "Input.h"
#include "Renderer.h"
#include <chrono>
#include <random>
#include <queue>
#include <memory>
#include <functional>

namespace Tetris {

/**
 * @brief Game state enumeration
 */
enum class GameState : uint8_t {
    MENU = 0,
    PLAYING,
    PAUSED,
    GAME_OVER,
    HELP,
    EXITING
};

/**
 * @brief Game difficulty configuration
 */
struct GameDifficulty {
    std::chrono::milliseconds initial_drop_speed{1000};     // Starting drop speed
    std::chrono::milliseconds min_drop_speed{50};           // Fastest possible drop speed
    int lines_per_level{10};                                // Lines to clear per level
    double speed_multiplier{0.9};                           // Speed increase factor per level
    int max_level{20};                                      // Maximum level
    
    GameDifficulty() = default;
    
    /**
     * @brief Calculate drop speed for a given level
     * @param level Current game level
     * @return Drop speed in milliseconds
     */
    [[nodiscard]] std::chrono::milliseconds getDropSpeed(int level) const {
        auto speed = initial_drop_speed;
        for (int i = 1; i < level && i <= max_level; ++i) {
            speed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::duration<double, std::milli>(speed.count() * speed_multiplier)
            );
        }
        return std::max(speed, min_drop_speed);
    }
};

/**
 * @brief Score calculation configuration
 */
struct ScoreConfig {
    int single_line{100};      // Points for clearing 1 line
    int double_line{300};      // Points for clearing 2 lines
    int triple_line{500};      // Points for clearing 3 lines
    int tetris_line{800};      // Points for clearing 4 lines (Tetris)
    int soft_drop{1};          // Points per cell for soft drop
    int hard_drop{2};          // Points per cell for hard drop
    int level_multiplier{1};   // Multiply base score by level
    
    ScoreConfig() = default;
    
    /**
     * @brief Calculate score for line clears
     * @param lines_cleared Number of lines cleared
     * @param level Current level
     * @return Score points earned
     */
    [[nodiscard]] int calculateLineScore(int lines_cleared, int level) const {
        int base_score = 0;
        switch (lines_cleared) {
            case 1: base_score = single_line; break;
            case 2: base_score = double_line; break;
            case 3: base_score = triple_line; break;
            case 4: base_score = tetris_line; break;
            default: break;
        }
        return base_score * (level * level_multiplier + 1);
    }
};

/**
 * @brief Main Tetris game controller
 * 
 * This class manages the complete game state, including the game loop,
 * piece generation, scoring, level progression, and user interface.
 * Designed for high performance with efficient timing and input handling.
 */
class TetrisGame {
public:
    using GameOverCallback = std::function<void(int final_score, int final_level)>;
    using LevelUpCallback = std::function<void(int new_level)>;
    using ScoreUpdateCallback = std::function<void(int new_score, int lines_cleared)>;
    
    /**
     * @brief Game configuration structure
     */
    struct Config {
        GameDifficulty difficulty;
        ScoreConfig score_config;
        RenderConfig render_config;
        InputHandler::Config input_config;
        bool enable_hold{true};              // Allow piece holding
        bool enable_ghost_piece{true};       // Show ghost piece preview
        bool enable_7_bag{true};             // Use 7-bag piece generation
        int next_piece_preview_count{1};     // Number of next pieces to show
        
        Config() = default;
    };
    
    /**
     * @brief Construct game with default configuration
     */
    TetrisGame();
    
    /**
     * @brief Construct game with custom configuration
     * @param config Game configuration
     */
    explicit TetrisGame(const Config& config);
    
    /**
     * @brief Destructor
     */
    ~TetrisGame();
    
    // Non-copyable but movable
    TetrisGame(const TetrisGame&) = delete;
    TetrisGame& operator=(const TetrisGame&) = delete;
    TetrisGame(TetrisGame&&) = default;
    TetrisGame& operator=(TetrisGame&&) = default;
    
    /**
     * @brief Initialize the game systems
     * @return True if initialization successful
     */
    bool initialize();
    
    /**
     * @brief Run the main game loop
     * @return Exit code (0 = normal exit)
     */
    int run();
    
    /**
     * @brief Shutdown game and cleanup resources
     */
    void shutdown();
    
    /**
     * @brief Start a new game
     */
    void startNewGame();
    
    /**
     * @brief Pause or unpause the game
     */
    void togglePause();
    
    /**
     * @brief Check if game is currently running
     * @return True if game is in progress
     */
    [[nodiscard]] bool isRunning() const noexcept { return state_ != GameState::EXITING; }
    
    /**
     * @brief Check if game is paused
     * @return True if game is paused
     */
    [[nodiscard]] bool isPaused() const noexcept { return state_ == GameState::PAUSED; }
    
    /**
     * @brief Check if game is over
     * @return True if game is over
     */
    [[nodiscard]] bool isGameOver() const noexcept { return state_ == GameState::GAME_OVER; }
    
    /**
     * @brief Get current game state
     * @return Current GameState
     */
    [[nodiscard]] GameState getState() const noexcept { return state_; }
    
    /**
     * @brief Get current score
     * @return Current game score
     */
    [[nodiscard]] int getScore() const noexcept { return score_; }
    
    /**
     * @brief Get current level
     * @return Current game level
     */
    [[nodiscard]] int getLevel() const noexcept { return level_; }
    
    /**
     * @brief Get total lines cleared
     * @return Total lines cleared this game
     */
    [[nodiscard]] int getLinesCleared() const noexcept { return total_lines_cleared_; }
    
    /**
     * @brief Get current falling piece
     * @return Reference to current Tetromino
     */
    [[nodiscard]] const Tetromino& getCurrentPiece() const noexcept { return current_piece_; }
    
    /**
     * @brief Get next piece
     * @return Reference to next Tetromino
     */
    [[nodiscard]] const Tetromino& getNextPiece() const noexcept { return next_piece_; }
    
    /**
     * @brief Get held piece
     * @return Reference to held Tetromino
     */
    [[nodiscard]] const Tetromino& getHeldPiece() const noexcept { return held_piece_; }
    
    /**
     * @brief Check if hold action is available
     * @return True if player can hold current piece
     */
    [[nodiscard]] bool canHold() const noexcept { return can_hold_; }
    
    /**
     * @brief Get game board
     * @return Reference to game Board
     */
    [[nodiscard]] const Board& getBoard() const noexcept { return board_; }
    
    /**
     * @brief Set game over callback
     * @param callback Function to call on game over
     */
    void setGameOverCallback(const GameOverCallback& callback) { game_over_callback_ = callback; }
    
    /**
     * @brief Set level up callback
     * @param callback Function to call on level up
     */
    void setLevelUpCallback(const LevelUpCallback& callback) { level_up_callback_ = callback; }
    
    /**
     * @brief Set score update callback
     * @param callback Function to call on score change
     */
    void setScoreUpdateCallback(const ScoreUpdateCallback& callback) { score_update_callback_ = callback; }
    
    /**
     * @brief Update game configuration
     * @param config New configuration
     */
    void setConfig(const Config& config) { config_ = config; }
    
    /**
     * @brief Get current game configuration
     * @return Current configuration
     */
    [[nodiscard]] const Config& getConfig() const noexcept { return config_; }
    
    /**
     * @brief Get high-resolution game statistics
     * @return Detailed game statistics
     */
    struct DetailedStats {
        int score{0};
        int level{1};
        int lines_cleared{0};
        int total_pieces{0};
        std::chrono::steady_clock::time_point game_start_time;
        std::chrono::milliseconds total_play_time{0};
        std::array<int, 7> piece_counts{}; // Count of each piece type
        int tetris_count{0};               // Number of 4-line clears
        int max_combo{0};                  // Maximum line clear combo
        double pieces_per_second{0.0};
        
        DetailedStats() : game_start_time(std::chrono::steady_clock::now()) {}
    };
    
    /**
     * @brief Get detailed game statistics
     * @return DetailedStats structure
     */
    [[nodiscard]] DetailedStats getDetailedStats() const;

private:
    Config config_;
    GameState state_{GameState::MENU};
    
    // Game systems
    Board board_;
    InputSystem input_system_;
    RenderSystem render_system_;
    
    // Game state
    Tetromino current_piece_;
    Tetromino next_piece_;
    Tetromino held_piece_;
    bool can_hold_{true};
    
    // Scoring and progression
    int score_{0};
    int level_{1};
    int total_lines_cleared_{0};
    int lines_cleared_this_level_{0};
    
    // Timing
    std::chrono::steady_clock::time_point last_drop_time_;
    std::chrono::steady_clock::time_point last_input_time_;
    std::chrono::steady_clock::time_point game_start_time_;
    std::chrono::milliseconds current_drop_speed_;
    
    // Piece generation
    std::mt19937 rng_;
    std::queue<TetrominoType> piece_bag_;
    int total_pieces_generated_{0};
    
    // Statistics
    DetailedStats stats_;
    
    // Callbacks
    GameOverCallback game_over_callback_;
    LevelUpCallback level_up_callback_;
    ScoreUpdateCallback score_update_callback_;
    
    /**
     * @brief Update game logic for one frame
     * @param delta_time Time elapsed since last update
     */
    void update(std::chrono::milliseconds delta_time);
    
    /**
     * @brief Render current game state
     */
    void render();
    
    /**
     * @brief Handle input events
     * @param input Current input state
     */
    void handleInput(const InputState& input);
    
    /**
     * @brief Process game logic when playing
     * @param delta_time Time elapsed since last update
     */
    void updateGameplay(std::chrono::milliseconds delta_time);
    
    /**
     * @brief Handle menu navigation
     * @param input Current input state
     */
    void handleMenuInput(const InputState& input);
    
    /**
     * @brief Handle pause screen input
     * @param input Current input state
     */
    void handlePauseInput(const InputState& input);
    
    /**
     * @brief Handle game over screen input
     * @param input Current input state
     */
    void handleGameOverInput(const InputState& input);
    
    /**
     * @brief Move current piece if possible
     * @param direction Movement direction
     * @return True if move was successful
     */
    bool movePiece(const Position& direction);
    
    /**
     * @brief Rotate current piece if possible
     * @param clockwise True for clockwise rotation
     * @return True if rotation was successful
     */
    bool rotatePiece(bool clockwise);
    
    /**
     * @brief Perform hard drop of current piece
     * @return Number of cells dropped
     */
    int hardDropPiece();
    
    /**
     * @brief Perform soft drop of current piece
     * @return True if piece moved down
     */
    bool softDropPiece();
    
    /**
     * @brief Hold current piece (swap with held piece)
     * @return True if hold was successful
     */
    bool holdPiece();
    
    /**
     * @brief Lock current piece to board and spawn next piece
     */
    void lockPiece();
    
    /**
     * @brief Spawn next piece as current piece
     * @return True if spawn was successful (false = game over)
     */
    bool spawnNextPiece();
    
    /**
     * @brief Generate next piece using 7-bag or random algorithm
     */
    void generateNextPiece();
    
    /**
     * @brief Fill piece bag with randomized sequence
     */
    void fillPieceBag();
    
    /**
     * @brief Update score based on lines cleared
     * @param lines_cleared Number of lines cleared
     */
    void updateScore(int lines_cleared);
    
    /**
     * @brief Update level based on lines cleared
     */
    void updateLevel();
    
    /**
     * @brief Update drop speed based on current level
     */
    void updateDropSpeed();
    
    /**
     * @brief Check if it's time for automatic piece drop
     * @return True if piece should drop
     */
    [[nodiscard]] bool shouldDropPiece() const;
    
    /**
     * @brief Reset game state for new game
     */
    void resetGameState();
    
    /**
     * @brief Update game statistics
     */
    void updateStats();
    
    /**
     * @brief Get GameStats structure for rendering
     * @return Current game statistics for display
     */
    [[nodiscard]] GameStats getGameStatsForRender() const;
    
    /**
     * @brief Check and handle game over condition
     * @return True if game is over
     */
    bool checkGameOver();
    
    /**
     * @brief Initialize random number generator
     */
    void initializeRNG();
    
    /**
     * @brief Get frame time target for smooth gameplay
     * @return Target frame duration
     */
    [[nodiscard]] std::chrono::milliseconds getTargetFrameTime() const {
        return std::chrono::milliseconds(16); // ~60 FPS
    }
};

/**
 * @brief Factory function to create a standard Tetris game
 * @return New TetrisGame instance with default configuration
 */
[[nodiscard]] std::unique_ptr<TetrisGame> createStandardGame();

/**
 * @brief Factory function to create a custom Tetris game
 * @param config Game configuration
 * @return New TetrisGame instance with specified configuration
 */
[[nodiscard]] std::unique_ptr<TetrisGame> createCustomGame(const TetrisGame::Config& config);

} // namespace Tetris
#pragma once

#include "Board.h"
#include "Tetromino.h"
#include <string>
#include <vector>
#include <array>
#include <memory>
#include <sstream>

namespace Tetris {

/**
 * @brief Color enumeration for console rendering
 */
enum class Color : uint8_t {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_RED = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_YELLOW = 11,
    BRIGHT_BLUE = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_CYAN = 14,
    BRIGHT_WHITE = 15
};

/**
 * @brief Console rendering configuration
 */
struct RenderConfig {
    bool use_colors{true};              // Enable colored output
    bool use_unicode{true};             // Use Unicode box drawing characters
    bool show_ghost_piece{true};        // Show ghost piece preview
    bool show_grid_lines{false};        // Show grid background
    bool double_width{true};            // Use double-width characters for blocks
    char filled_char{'#'};              // Character for filled blocks (ASCII mode)
    char empty_char{' '};               // Character for empty spaces
    char border_char{'|'};              // Character for borders (ASCII mode)
    
    RenderConfig() = default;
};

/**
 * @brief Game statistics for display
 */
struct GameStats {
    int score{0};
    int level{1};
    int lines_cleared{0};
    int total_pieces{0};
    TetrominoType next_piece{TetrominoType::NONE};
    TetrominoType held_piece{TetrominoType::NONE};
    bool can_hold{true};
    
    GameStats() = default;
};

/**
 * @brief Console renderer for Tetris game
 * 
 * This class handles all console output for the Tetris game including
 * board rendering, piece display, UI elements, and cross-platform
 * console manipulation. Optimized for minimal screen updates and
 * supports both colored and monochrome displays.
 */
class ConsoleRenderer {
public:
    /**
     * @brief Construct renderer with default configuration
     */
    ConsoleRenderer();
    
    /**
     * @brief Construct renderer with custom configuration
     * @param config Rendering configuration
     */
    explicit ConsoleRenderer(const RenderConfig& config);
    
    /**
     * @brief Destructor - cleanup console state
     */
    ~ConsoleRenderer();
    
    // Non-copyable but movable
    ConsoleRenderer(const ConsoleRenderer&) = delete;
    ConsoleRenderer& operator=(const ConsoleRenderer&) = delete;
    ConsoleRenderer(ConsoleRenderer&&) = default;
    ConsoleRenderer& operator=(ConsoleRenderer&&) = default;
    
    /**
     * @brief Initialize the renderer and console
     * @return True if initialization successful
     */
    bool initialize();
    
    /**
     * @brief Shutdown renderer and restore console state
     */
    void shutdown();
    
    /**
     * @brief Clear the entire screen
     */
    void clearScreen();
    
    /**
     * @brief Render the complete game state
     * @param board Game board to render
     * @param current_piece Current falling piece
     * @param stats Game statistics
     */
    void render(const Board& board, const Tetromino& current_piece, const GameStats& stats);
    
    /**
     * @brief Render only the game board (optimized update)
     * @param board Game board to render
     * @param current_piece Current falling piece
     */
    void renderBoard(const Board& board, const Tetromino& current_piece);
    
    /**
     * @brief Render game statistics panel
     * @param stats Game statistics to display
     */
    void renderStats(const GameStats& stats);
    
    /**
     * @brief Render next piece preview
     * @param next_piece Next piece to display
     */
    void renderNextPiece(const Tetromino& next_piece);
    
    /**
     * @brief Render held piece display
     * @param held_piece Held piece to display
     * @param can_hold Whether hold action is available
     */
    void renderHeldPiece(const Tetromino& held_piece, bool can_hold);
    
    /**
     * @brief Display game over screen
     * @param final_score Final game score
     * @param final_level Final game level
     */
    void renderGameOver(int final_score, int final_level);
    
    /**
     * @brief Display pause screen
     */
    void renderPause();
    
    /**
     * @brief Display main menu
     * @param selected_option Currently selected menu option
     */
    void renderMenu(int selected_option);
    
    /**
     * @brief Display help/controls screen
     */
    void renderHelp();
    
    /**
     * @brief Update rendering configuration
     * @param config New configuration settings
     */
    void setConfig(const RenderConfig& config) { config_ = config; }
    
    /**
     * @brief Get current rendering configuration
     * @return Current configuration settings
     */
    [[nodiscard]] const RenderConfig& getConfig() const noexcept { return config_; }
    
    /**
     * @brief Get console dimensions
     * @return Width and height of console
     */
    [[nodiscard]] Position getConsoleDimensions() const;
    
    /**
     * @brief Check if renderer is initialized
     * @return True if ready for rendering
     */
    [[nodiscard]] bool isInitialized() const noexcept { return initialized_; }
    
    /**
     * @brief Enable or disable cursor visibility
     * @param visible True to show cursor
     */
    void setCursorVisible(bool visible);
    
    /**
     * @brief Move cursor to specific position
     * @param x X coordinate
     * @param y Y coordinate
     */
    void setCursorPosition(int x, int y);
    
    /**
     * @brief Set text color for subsequent output
     * @param color Text color to use
     */
    void setTextColor(Color color);
    
    /**
     * @brief Set background color for subsequent output
     * @param color Background color to use
     */
    void setBackgroundColor(Color color);
    
    /**
     * @brief Reset console colors to default
     */
    void resetColors();
    
    /**
     * @brief Force a complete screen refresh
     */
    void refresh();
    
    /**
     * @brief Get string representation of a Tetromino piece (for debug)
     * @param piece Piece to convert to string
     * @return Multi-line string representation
     */
    [[nodiscard]] std::string pieceToString(const Tetromino& piece) const;

private:
    RenderConfig config_;
    bool initialized_{false};
    Position console_size_{80, 24}; // Default console size
    
    // Platform-specific console handling
    struct PlatformData;
    std::unique_ptr<PlatformData> platform_data_;
    
    // Cached rendering data for optimization
    mutable std::vector<std::string> board_cache_;
    mutable bool cache_dirty_{true};
    
    /**
     * @brief Platform-specific initialization
     * @return True if successful
     */
    bool platformInitialize();
    
    /**
     * @brief Platform-specific shutdown
     */
    void platformShutdown();
    
    /**
     * @brief Platform-specific screen clearing
     */
    void platformClearScreen();
    
    /**
     * @brief Platform-specific cursor positioning
     * @param x X coordinate
     * @param y Y coordinate
     */
    void platformSetCursorPosition(int x, int y);
    
    /**
     * @brief Platform-specific color setting
     * @param text_color Text color
     * @param bg_color Background color
     */
    void platformSetColors(Color text_color, Color bg_color);
    
    /**
     * @brief Platform-specific console size detection
     * @return Console dimensions
     */
    [[nodiscard]] Position platformGetConsoleSize() const;
    
    /**
     * @brief Platform-specific cursor visibility control
     * @param visible True to show cursor
     */
    void platformSetCursorVisible(bool visible);
    
    /**
     * @brief Render a single board cell
     * @param cell Cell to render
     * @param x X position
     * @param y Y position
     * @param show_ghost Whether this is a ghost piece cell
     */
    void renderCell(const Cell& cell, int x, int y, bool show_ghost = false);
    
    /**
     * @brief Render board borders and frame
     */
    void renderBoardFrame();
    
    /**
     * @brief Get color for a piece type
     * @param piece_type Type of Tetromino piece
     * @return Corresponding color
     */
    [[nodiscard]] Color getPieceColor(TetrominoType piece_type) const noexcept;
    
    /**
     * @brief Get Unicode character for filled block
     * @return Unicode block character
     */
    [[nodiscard]] const char* getBlockChar() const noexcept;
    
    /**
     * @brief Get Unicode character for border elements
     * @param type Border type (horizontal, vertical, corner, etc.)
     * @return Unicode border character
     */
    [[nodiscard]] const char* getBorderChar(int type) const noexcept;
    
    /**
     * @brief Create a formatted string with padding
     * @param text Text to format
     * @param width Target width
     * @param align Alignment (0=left, 1=center, 2=right)
     * @return Formatted string
     */
    [[nodiscard]] std::string formatText(const std::string& text, int width, int align = 0) const;
    
    /**
     * @brief Calculate board render position
     * @return Starting position for board rendering
     */
    [[nodiscard]] Position getBoardRenderPosition() const;
    
    /**
     * @brief Calculate stats panel position
     * @return Starting position for stats panel
     */
    [[nodiscard]] Position getStatsPanelPosition() const;
    
    /**
     * @brief Render a small piece preview (4x4 grid)
     * @param piece Piece to render
     * @param start_x Starting X position
     * @param start_y Starting Y position
     * @param title Optional title above the piece
     */
    void renderPiecePreview(const Tetromino& piece, int start_x, int start_y, 
                           const std::string& title = "");
    
    /**
     * @brief Output text at current cursor position
     * @param text Text to output
     */
    void printText(const std::string& text);
    
    /**
     * @brief Output text at specific position
     * @param x X coordinate
     * @param y Y coordinate
     * @param text Text to output
     */
    void printTextAt(int x, int y, const std::string& text);
    
    /**
     * @brief Invalidate render cache
     */
    void invalidateCache() { cache_dirty_ = true; }
};

/**
 * @brief RAII wrapper for console renderer
 */
class RenderSystem {
public:
    /**
     * @brief Initialize render system with default configuration
     */
    RenderSystem();
    
    /**
     * @brief Initialize render system with custom configuration
     * @param config Render configuration
     */
    explicit RenderSystem(const RenderConfig& config);
    
    /**
     * @brief Destructor ensures proper cleanup
     */
    ~RenderSystem();
    
    // Non-copyable and non-movable
    RenderSystem(const RenderSystem&) = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;
    RenderSystem(RenderSystem&&) = delete;
    RenderSystem& operator=(RenderSystem&&) = delete;
    
    /**
     * @brief Get the renderer instance
     * @return Reference to the console renderer
     */
    [[nodiscard]] ConsoleRenderer& getRenderer() noexcept { return renderer_; }
    
    /**
     * @brief Check if system is ready for rendering
     * @return True if system is initialized
     */
    [[nodiscard]] bool isReady() const noexcept { return renderer_.isInitialized(); }

private:
    ConsoleRenderer renderer_;
};

} // namespace Tetris
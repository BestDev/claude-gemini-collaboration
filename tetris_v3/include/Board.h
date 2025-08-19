#pragma once

#include "Tetromino.h"
#include <array>
#include <vector>
#include <cstdint>
#include <functional>

namespace Tetris {

/**
 * @brief Board cell structure representing a single grid position
 */
struct Cell {
    bool occupied{false};
    uint8_t color{0}; // Color index for rendering (0 = empty, 1-7 = piece colors)
    
    Cell() = default;
    Cell(bool occ, uint8_t col) : occupied(occ), color(col) {}
    
    void clear() noexcept {
        occupied = false;
        color = 0;
    }
    
    void set(uint8_t piece_color) noexcept {
        occupied = true;
        color = piece_color;
    }
    
    bool isEmpty() const noexcept { return !occupied; }
};

/**
 * @brief Game board class managing the 10x20 Tetris playing field
 * 
 * This class handles the game board state, piece placement validation,
 * line clearing mechanics, and collision detection. Uses efficient
 * data structures and algorithms for optimal performance.
 */
class Board {
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    static constexpr int SPAWN_X = WIDTH / 2 - 2; // Center spawn position
    static constexpr int SPAWN_Y = 0;
    
    using GridType = std::array<std::array<Cell, WIDTH>, HEIGHT>;
    using LineCallback = std::function<void(int line_count, int level)>;
    
    /**
     * @brief Construct an empty board
     */
    Board();
    
    /**
     * @brief Clear the entire board
     */
    void clear() noexcept;
    
    /**
     * @brief Check if a position is within board boundaries
     * @param pos Position to check
     * @return True if position is valid
     */
    [[nodiscard]] bool isValidPosition(const Position& pos) const noexcept;
    
    /**
     * @brief Check if a cell is empty
     * @param pos Position to check
     * @return True if cell is empty and within bounds
     */
    [[nodiscard]] bool isEmpty(const Position& pos) const noexcept;
    
    /**
     * @brief Check if a cell is occupied
     * @param pos Position to check
     * @return True if cell is occupied
     */
    [[nodiscard]] bool isOccupied(const Position& pos) const noexcept;
    
    /**
     * @brief Get cell at specified position
     * @param pos Position to get
     * @return Reference to the cell (const version)
     */
    [[nodiscard]] const Cell& getCell(const Position& pos) const;
    
    /**
     * @brief Get cell at specified position
     * @param pos Position to get
     * @return Reference to the cell (non-const version)
     */
    [[nodiscard]] Cell& getCell(const Position& pos);
    
    /**
     * @brief Get cell at specified coordinates
     * @param x X coordinate
     * @param y Y coordinate
     * @return Reference to the cell (const version)
     */
    [[nodiscard]] const Cell& getCell(int x, int y) const;
    
    /**
     * @brief Check if a Tetromino can be placed at its current position
     * @param piece The Tetromino to check
     * @return True if placement is valid
     */
    [[nodiscard]] bool canPlacePiece(const Tetromino& piece) const;
    
    /**
     * @brief Check if a Tetromino can be placed at a specific position and rotation
     * @param piece The Tetromino to check
     * @param pos Position to check
     * @param rot Rotation to check
     * @return True if placement is valid
     */
    [[nodiscard]] bool canPlacePiece(const Tetromino& piece, const Position& pos, Rotation rot) const;
    
    /**
     * @brief Place a Tetromino on the board permanently
     * @param piece The Tetromino to place
     * @return True if piece was successfully placed
     */
    bool placePiece(const Tetromino& piece);
    
    /**
     * @brief Check for and clear complete lines
     * @return Number of lines cleared
     */
    int clearLines();
    
    /**
     * @brief Check if a specific line is complete
     * @param line Line index to check
     * @return True if line is complete
     */
    [[nodiscard]] bool isLineComplete(int line) const;
    
    /**
     * @brief Check if the board is in game over state (top row occupied)
     * @return True if game over
     */
    [[nodiscard]] bool isGameOver() const;
    
    /**
     * @brief Get the current board grid
     * @return Const reference to the board grid
     */
    [[nodiscard]] const GridType& getGrid() const noexcept { return grid_; }
    
    /**
     * @brief Find the lowest valid position for a piece (hard drop calculation)
     * @param piece The Tetromino to drop
     * @return Position where the piece would land
     */
    [[nodiscard]] Position findDropPosition(const Tetromino& piece) const;
    
    /**
     * @brief Get a preview of the board with a piece placed (for ghost piece rendering)
     * @param piece The Tetromino to preview
     * @param ghost_color Color index for ghost piece (default 8 for gray)
     * @return Copy of board with ghost piece overlaid
     */
    [[nodiscard]] Board getPreviewBoard(const Tetromino& piece, uint8_t ghost_color = 8) const;
    
    /**
     * @brief Check how many lines are currently complete
     * @return Number of complete lines
     */
    [[nodiscard]] int countCompleteLines() const;
    
    /**
     * @brief Get all complete line indices
     * @return Vector of line indices that are complete
     */
    [[nodiscard]] std::vector<int> getCompleteLines() const;
    
    /**
     * @brief Set callback for line clearing events
     * @param callback Function to call when lines are cleared
     */
    void setLineClearCallback(const LineCallback& callback) { line_clear_callback_ = callback; }
    
    /**
     * @brief Get the height of the highest occupied cell in a column
     * @param column Column index to check
     * @return Height of highest occupied cell (0 = empty column)
     */
    [[nodiscard]] int getColumnHeight(int column) const;
    
    /**
     * @brief Get board statistics for AI or analysis
     * @return Structure containing board metrics
     */
    struct BoardStats {
        int total_height{0};        // Sum of all column heights
        int max_height{0};          // Highest column
        int holes{0};               // Count of empty cells below occupied cells
        int bumpiness{0};           // Sum of height differences between adjacent columns
        int complete_lines{0};      // Number of complete lines
    };
    
    /**
     * @brief Calculate board statistics
     * @return BoardStats structure with current metrics
     */
    [[nodiscard]] BoardStats calculateStats() const;
    
    /**
     * @brief Reset board to initial empty state
     */
    void reset() noexcept;

private:
    GridType grid_;
    LineCallback line_clear_callback_;
    
    /**
     * @brief Remove a specific line and shift everything down
     * @param line Line index to remove
     */
    void removeLine(int line);
    
    /**
     * @brief Check bounds for position
     * @param x X coordinate
     * @param y Y coordinate
     * @return True if position is within bounds
     */
    [[nodiscard]] bool isInBounds(int x, int y) const noexcept {
        return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
    }
    
    /**
     * @brief Get occupied positions for a piece at specific position and rotation
     * @param piece The piece to check
     * @param pos Position offset
     * @param rot Rotation state
     * @return Vector of absolute positions the piece would occupy
     */
    [[nodiscard]] std::vector<Position> getPiecePositions(const Tetromino& piece, 
                                                          const Position& pos, 
                                                          Rotation rot) const;
};

/**
 * @brief Factory function to create a standard Tetris board
 * @return New empty Board instance
 */
[[nodiscard]] Board createStandardBoard();

} // namespace Tetris
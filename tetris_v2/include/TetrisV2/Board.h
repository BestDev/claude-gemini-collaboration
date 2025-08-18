/**
 * @file Board.h
 * @brief Board class representing the game grid and its state
 * 
 * This class manages the game board, handles collision detection,
 * places tetrominoes, and clears completed lines.
 */

#ifndef TETRISV2_BOARD_H
#define TETRISV2_BOARD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"

namespace TetrisV2 {

/**
 * @brief Represents the main game board and its state
 * 
 * This class manages the grid of landed blocks, checks for collisions,
 * and handles line clearing logic. It maintains the state of all
 * permanently placed blocks on the game board.
 */
class Board {
public:
    /**
     * @brief Construct a new Board object
     * 
     * Initializes an empty game board with the standard Tetris dimensions.
     */
    Board();

    /**
     * @brief Check if a tetromino would collide with the board or other pieces
     * @param tetromino The tetromino to check for collision
     * @return true if there would be a collision, false otherwise
     * 
     * This function checks if the tetromino's current position would result
     * in a collision with the board boundaries or already placed blocks.
     */
    bool isCollision(const Tetromino& tetromino) const;

    /**
     * @brief Place a tetromino permanently on the board
     * @param tetromino The tetromino to place
     * 
     * Adds the tetromino's blocks to the board's permanent grid.
     * This should only be called after ensuring there are no collisions.
     */
    void placePiece(const Tetromino& tetromino);

    /**
     * @brief Clear completed lines and return the number cleared
     * @return The number of lines that were cleared
     * 
     * Scans the board for complete lines, removes them, and drops
     * all lines above down to fill the gaps.
     */
    int clearLines();

    /**
     * @brief Get the current state of the game grid
     * @return 2D vector representing the board state
     * 
     * Returns a reference to the internal grid where each cell contains
     * either a color (if filled) or a transparent color (if empty).
     */
    const std::vector<std::vector<sf::Color>>& getGrid() const;

    /**
     * @brief Check if a specific cell is occupied
     * @param x X coordinate (column)
     * @param y Y coordinate (row)
     * @return true if the cell is occupied, false if empty or out of bounds
     */
    bool isCellOccupied(int x, int y) const;

    /**
     * @brief Check if the game is over (pieces reached the top)
     * @return true if the game should end, false otherwise
     * 
     * Game over occurs when a newly spawned piece would immediately collide.
     */
    bool isGameOver() const;

    /**
     * @brief Reset the board to its initial empty state
     * 
     * Clears all placed blocks and resets the board for a new game.
     */
    void reset();

    /**
     * @brief Get the height of the highest placed block
     * @return The row number of the highest block (0 = top), or BOARD_HEIGHT if empty
     */
    int getHighestBlockRow() const;

private:
    std::vector<std::vector<sf::Color>> m_grid; ///< The game board grid

    /**
     * @brief Check if coordinates are within the board boundaries
     * @param x X coordinate to check
     * @param y Y coordinate to check
     * @return true if coordinates are valid, false otherwise
     */
    bool isValidPosition(int x, int y) const;

    /**
     * @brief Check if a specific row is completely filled
     * @param row The row number to check
     * @return true if the row is complete, false otherwise
     */
    bool isRowComplete(int row) const;

    /**
     * @brief Remove a specific row and drop all rows above it
     * @param row The row number to remove
     */
    void removeRow(int row);

    /**
     * @brief Drop all rows above a given row down by one position
     * @param aboveRow All rows above this will be moved down
     */
    void dropRowsAbove(int aboveRow);
};

} // namespace TetrisV2

#endif // TETRISV2_BOARD_H
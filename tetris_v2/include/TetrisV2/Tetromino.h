/**
 * @file Tetromino.h
 * @brief Tetromino class representing individual Tetris pieces
 * 
 * This class manages a single Tetris piece (tetromino), including its shape,
 * position, rotation state, and movement operations.
 */

#ifndef TETRISV2_TETROMINO_H
#define TETRISV2_TETROMINO_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Constants.h"

namespace TetrisV2 {

/**
 * @brief Represents a single Tetris piece (tetromino)
 * 
 * This class encapsulates all the properties and behaviors of a tetromino,
 * including its shape, color, position, and rotation logic.
 */
class Tetromino {
public:
    /**
     * @brief Construct a new Tetromino object
     * @param type The type of tetromino to create (I, O, T, S, Z, J, L)
     */
    explicit Tetromino(TetrominoType type);

    /**
     * @brief Rotate the tetromino clockwise by 90 degrees
     * 
     * Changes the rotation state and updates the block positions accordingly.
     * Does not check for collisions - that should be done by the caller.
     */
    void rotate();

    /**
     * @brief Rotate the tetromino counterclockwise by 90 degrees
     * 
     * Used for wall kick attempts when normal rotation fails.
     */
    void rotateCounterClockwise();

    /**
     * @brief Move the tetromino by the specified offset
     * @param dx Horizontal displacement (positive = right, negative = left)
     * @param dy Vertical displacement (positive = down, negative = up)
     */
    void move(int dx, int dy);

    /**
     * @brief Set the absolute position of the tetromino
     * @param x New X coordinate
     * @param y New Y coordinate
     */
    void setPosition(int x, int y);

    /**
     * @brief Get the current position of the tetromino
     * @return The position as an sf::Vector2i (x, y)
     */
    sf::Vector2i getPosition() const;

    /**
     * @brief Get the block positions relative to the tetromino's position
     * @return Vector of relative block positions that make up this tetromino
     */
    const std::vector<sf::Vector2i>& getBlocks() const;

    /**
     * @brief Get the absolute positions of all blocks in the tetromino
     * @return Vector of absolute block positions on the game board
     */
    std::vector<sf::Vector2i> getAbsoluteBlocks() const;

    /**
     * @brief Get the color of this tetromino
     * @return The SFML color for rendering this tetromino
     */
    sf::Color getColor() const;

    /**
     * @brief Get the type of this tetromino
     * @return The TetrominoType enum value
     */
    TetrominoType getType() const;

    /**
     * @brief Get the current rotation state (0-3)
     * @return Current rotation state
     */
    int getRotation() const;

    /**
     * @brief Create a copy of this tetromino for testing rotations
     * @return A new Tetromino object with the same properties
     */
    Tetromino copy() const;

private:
    TetrominoType m_type;           ///< The type of this tetromino
    sf::Vector2i m_position;        ///< Current position on the board
    int m_rotation;                 ///< Current rotation state (0-3)
    std::vector<sf::Vector2i> m_blocks; ///< Relative block positions for current rotation

    /**
     * @brief Initialize the shape data for all rotation states
     * 
     * Sets up the m_blocks vector based on the tetromino type and rotation.
     * This is called during construction and after each rotation.
     */
    void initializeShape();

    /**
     * @brief Get the shape data for a specific tetromino type and rotation
     * @param type The tetromino type
     * @param rotation The rotation state (0-3)
     * @return Vector of relative block positions for the specified state
     */
    static std::vector<sf::Vector2i> getShapeData(TetrominoType type, int rotation);
};

} // namespace TetrisV2

#endif // TETRISV2_TETROMINO_H
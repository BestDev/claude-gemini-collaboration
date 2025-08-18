/**
 * @file Renderer.h
 * @brief Renderer class for drawing all game elements
 * 
 * This class handles all rendering operations including the game board,
 * tetrominoes, UI elements, and text display.
 */

#ifndef TETRISV2_RENDERER_H
#define TETRISV2_RENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "Board.h"
#include "Tetromino.h"

namespace TetrisV2 {

/**
 * @brief Handles all drawing operations for the game
 * 
 * This class is responsible for rendering the game board, pieces, UI elements,
 * and text. It provides a clean interface for the game to display all visual
 * elements without worrying about the underlying graphics implementation.
 */
class Renderer {
public:
    /**
     * @brief Construct a new Renderer object
     * @param window Reference to the SFML render window
     * 
     * Initializes the renderer and loads necessary resources like fonts.
     */
    explicit Renderer(sf::RenderWindow& window);

    /**
     * @brief Initialize the renderer (load fonts, etc.)
     * @return true if initialization succeeded, false otherwise
     * 
     * This must be called before using any other rendering functions.
     * It loads fonts and other resources needed for rendering.
     */
    bool initialize();

    /**
     * @brief Draw the game board background and grid
     * @param board The board to render
     * 
     * Draws the board background, grid lines, and all placed blocks.
     */
    void drawBoard(const Board& board);

    /**
     * @brief Draw a tetromino at its current position
     * @param tetromino The tetromino to render
     * 
     * Renders the tetromino with its proper color and position.
     */
    void drawTetromino(const Tetromino& tetromino);

    /**
     * @brief Draw a tetromino as a ghost piece (preview of where it will land)
     * @param tetromino The tetromino to render as a ghost
     * @param ghostY The Y position where the ghost should be drawn
     * 
     * Renders a semi-transparent version of the tetromino to show where it will land.
     */
    void drawGhostPiece(const Tetromino& tetromino, int ghostY);

    /**
     * @brief Draw text at a specified position
     * @param text The text to draw
     * @param position The position to draw the text
     * @param size The font size (default: 24)
     * @param color The text color (default: white)
     */
    void drawText(const std::string& text, sf::Vector2f position, 
                  unsigned int size = 24, sf::Color color = sf::Color::White);

    /**
     * @brief Draw the game UI (score, level, lines, etc.)
     * @param score Current game score
     * @param level Current game level
     * @param lines Number of lines cleared
     * @param nextPiece The next tetromino to be spawned (optional)
     */
    void drawUI(int score, int level, int lines, const Tetromino* nextPiece = nullptr);

    /**
     * @brief Draw the game over screen
     * @param finalScore The final score achieved
     */
    void drawGameOver(int finalScore);

    /**
     * @brief Draw the pause screen
     */
    void drawPauseScreen();

    /**
     * @brief Draw the main menu
     */
    void drawMainMenu();

    /**
     * @brief Clear the screen with the background color
     */
    void clear();

    /**
     * @brief Present the rendered frame to the screen
     */
    void display();

private:
    sf::RenderWindow& m_window;     ///< Reference to the SFML window
    sf::Font m_font;                ///< Font for text rendering
    sf::RectangleShape m_blockShape; ///< Reusable shape for drawing blocks
    bool m_fontLoaded;              ///< Whether the font was loaded successfully

    /**
     * @brief Draw a single block at the specified grid position
     * @param x Grid X coordinate
     * @param y Grid Y coordinate
     * @param color Block color
     * @param alpha Alpha transparency (default: 255 for opaque)
     */
    void drawBlock(int x, int y, sf::Color color, sf::Uint8 alpha = 255);

    /**
     * @brief Draw the grid lines for the game board
     */
    void drawGrid();

    /**
     * @brief Draw the border around the game board
     */
    void drawBoardBorder();

    /**
     * @brief Draw a preview of the next piece
     * @param nextPiece The next tetromino to preview
     * @param position Position to draw the preview
     */
    void drawNextPiecePreview(const Tetromino& nextPiece, sf::Vector2f position);

    /**
     * @brief Convert grid coordinates to screen coordinates
     * @param gridX Grid X coordinate
     * @param gridY Grid Y coordinate
     * @return Screen position as sf::Vector2f
     */
    sf::Vector2f gridToScreen(int gridX, int gridY) const;
};

} // namespace TetrisV2

#endif // TETRISV2_RENDERER_H
/**
 * @file Constants.h
 * @brief Global game constants for Tetris V2
 * 
 * This header defines all the game-wide constants to avoid magic numbers
 * and provide a central location for game configuration parameters.
 */

#ifndef TETRISV2_CONSTANTS_H
#define TETRISV2_CONSTANTS_H

#include <SFML/Graphics.hpp>

namespace TetrisV2 {

// Board dimensions in blocks
constexpr int BOARD_WIDTH = 10;
constexpr int BOARD_HEIGHT = 20;

// Visual settings
constexpr int BLOCK_SIZE = 30;  // Size of a single block in pixels
constexpr int WINDOW_WIDTH = BOARD_WIDTH * BLOCK_SIZE + 200;  // Extra space for UI
constexpr int WINDOW_HEIGHT = BOARD_HEIGHT * BLOCK_SIZE + 100; // Extra space for UI

// Game timing
constexpr int FRAME_RATE_LIMIT = 60;
constexpr float INITIAL_DROP_TIME = 1.0f;  // Time between automatic piece drops (seconds)
constexpr float DROP_TIME_DECREASE = 0.05f; // How much faster each level gets

// Scoring
constexpr int POINTS_PER_LINE = 100;
constexpr int LEVEL_UP_LINES = 10;  // Lines needed to advance to next level

// Input timing
constexpr float KEY_REPEAT_DELAY = 0.15f;  // Delay for key repeat in seconds

// Tetromino types
enum class TetrominoType {
    I, O, T, S, Z, J, L
};

// Game states
enum class GameState {
    Menu,
    Playing,
    Paused,
    GameOver
};

// Colors for each tetromino type
const sf::Color TETROMINO_COLORS[] = {
    sf::Color::Cyan,    // I
    sf::Color::Yellow,  // O
    sf::Color::Magenta, // T
    sf::Color::Green,   // S
    sf::Color::Red,     // Z
    sf::Color::Blue,    // J
    sf::Color(255, 165, 0) // L (Orange)
};

// Grid colors
const sf::Color EMPTY_CELL_COLOR = sf::Color(40, 40, 40);
const sf::Color GRID_LINE_COLOR = sf::Color(80, 80, 80);
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

// UI positioning
constexpr int BOARD_OFFSET_X = 10;
constexpr int BOARD_OFFSET_Y = 50;
constexpr int UI_PANEL_X = BOARD_WIDTH * BLOCK_SIZE + 30;
constexpr int SCORE_Y = 60;
constexpr int LEVEL_Y = 100;
constexpr int LINES_Y = 140;

} // namespace TetrisV2

#endif // TETRISV2_CONSTANTS_H
/**
 * @file Game.h
 * @brief Game class managing the main game loop and game state
 * 
 * This class serves as the main game engine, coordinating all game systems
 * and managing the overall game state and flow.
 */

#ifndef TETRISV2_GAME_H
#define TETRISV2_GAME_H

#include <SFML/Graphics.hpp>
#include <random>
#include <optional>
#include "Constants.h"
#include "Board.h"
#include "Renderer.h"
#include "Tetromino.h"

namespace TetrisV2 {

/**
 * @brief Main game engine coordinating all game systems
 * 
 * This class owns the main game loop and manages the game state,
 * user input handling, game logic progression, and coordination
 * between all other game systems.
 */
class Game {
public:
    /**
     * @brief Construct a new Game object
     * 
     * Initializes the game window, renderer, and all game systems.
     */
    Game();

    /**
     * @brief Run the main game loop
     * 
     * This is the main entry point that starts the game and runs
     * until the player exits.
     */
    void run();

private:
    // Core game objects
    sf::RenderWindow m_window;          ///< Main game window
    Board m_board;                      ///< Game board
    Renderer m_renderer;                ///< Rendering system
    
    // Game state
    GameState m_gameState;              ///< Current game state
    int m_score;                        ///< Current score
    int m_level;                        ///< Current level
    int m_linesCleared;                 ///< Total lines cleared
    int m_linesInCurrentLevel;          ///< Lines cleared in current level
    
    // Tetromino management
    std::optional<Tetromino> m_currentPiece;  ///< Currently falling piece
    std::optional<Tetromino> m_nextPiece;     ///< Next piece to spawn
    
    // Timing
    sf::Clock m_clock;                  ///< Main game clock
    sf::Clock m_dropClock;              ///< Clock for automatic piece dropping
    sf::Clock m_inputClock;             ///< Clock for input timing
    float m_dropTime;                   ///< Current drop time interval
    
    // Input state
    bool m_keyPressed[sf::Keyboard::KeyCount]; ///< Track pressed keys
    
    // Random number generation
    std::random_device m_randomDevice;  ///< Random device for seeding
    std::mt19937 m_rng;                 ///< Random number generator
    std::uniform_int_distribution<int> m_pieceDist; ///< Distribution for piece types

    /**
     * @brief Process user input
     * 
     * Handles keyboard input for game controls including movement,
     * rotation, pause, restart, etc.
     */
    void processInput();

    /**
     * @brief Update game logic
     * @param deltaTime Time elapsed since last update
     * 
     * Updates game state, handles piece movement, line clearing,
     * level progression, and other game logic.
     */
    void update(float deltaTime);

    /**
     * @brief Render the current game state
     * 
     * Draws all game elements appropriate for the current state.
     */
    void render();

    /**
     * @brief Spawn a new piece at the top of the board
     * 
     * Creates a new tetromino and places it at the spawn position.
     * If spawning fails due to collision, triggers game over.
     */
    void spawnNewPiece();

    /**
     * @brief Generate a random tetromino type
     * @return Random TetrominoType
     */
    TetrominoType getRandomPieceType();

    /**
     * @brief Try to move the current piece by the specified offset
     * @param dx Horizontal movement
     * @param dy Vertical movement
     * @return true if the move was successful, false if blocked
     */
    bool tryMovePiece(int dx, int dy);

    /**
     * @brief Try to rotate the current piece
     * @return true if rotation was successful, false if blocked
     * 
     * Attempts rotation with wall kick system for better playability.
     */
    bool tryRotatePiece();

    /**
     * @brief Drop the current piece as far down as possible
     * @return Points awarded for the drop
     */
    int hardDrop();

    /**
     * @brief Calculate where the current piece would land if dropped
     * @return Y coordinate where the piece would land
     */
    int calculateGhostPosition() const;

    /**
     * @brief Handle the placement of the current piece
     * 
     * Places the piece on the board, clears lines, updates score,
     * and spawns the next piece.
     */
    void placePieceAndClear();

    /**
     * @brief Update the score based on lines cleared and level
     * @param linesCleared Number of lines cleared in this action
     * @param hardDropLines Lines dropped during hard drop (optional)
     */
    void updateScore(int linesCleared, int hardDropLines = 0);

    /**
     * @brief Check if level should increase and update accordingly
     */
    void updateLevel();

    /**
     * @brief Calculate the current drop time based on level
     * @return Drop time in seconds
     */
    float calculateDropTime() const;

    /**
     * @brief Reset the game to initial state for a new game
     */
    void resetGame();

    /**
     * @brief Check if a key was just pressed (not held)
     * @param key The key to check
     * @return true if the key was just pressed this frame
     */
    bool isKeyJustPressed(sf::Keyboard::Key key);

    /**
     * @brief Update the key press state tracking
     */
    void updateKeyStates();

    /**
     * @brief Handle wall kick attempts for rotation
     * @param piece The piece attempting to rotate
     * @return true if wall kick was successful, false otherwise
     * 
     * Implements a simplified wall kick system to improve playability.
     */
    bool attemptWallKick(Tetromino& piece);
};

} // namespace TetrisV2

#endif // TETRISV2_GAME_H
/**
 * @file Game.cpp
 * @brief Implementation of the Game class
 */

#include "TetrisV2/Game.h"
#include <iostream>
#include <algorithm>

namespace TetrisV2 {

Game::Game() 
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris V2"),
      m_renderer(m_window),
      m_gameState(GameState::Menu),
      m_score(0),
      m_level(1),
      m_linesCleared(0),
      m_linesInCurrentLevel(0),
      m_dropTime(INITIAL_DROP_TIME),
      m_rng(m_randomDevice()),
      m_pieceDist(0, 6) {
    
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
    
    // Initialize key state tracking
    std::fill(std::begin(m_keyPressed), std::end(m_keyPressed), false);
    
    // Initialize renderer
    if (!m_renderer.initialize()) {
        std::cerr << "Warning: Renderer initialization had issues\n";
    }
}

void Game::run() {
    sf::Clock frameClock;
    
    while (m_window.isOpen()) {
        float deltaTime = frameClock.restart().asSeconds();
        
        processInput();
        
        if (m_gameState == GameState::Playing) {
            update(deltaTime);
        }
        
        render();
    }
}

void Game::processInput() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            return;
        }
        
        if (event.type == sf::Event::KeyPressed) {
            switch (m_gameState) {
                case GameState::Menu:
                    if (event.key.code == sf::Keyboard::Space) {
                        resetGame();
                        m_gameState = GameState::Playing;
                        spawnNewPiece();
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        m_window.close();
                    }
                    break;
                    
                case GameState::Playing:
                    if (event.key.code == sf::Keyboard::P) {
                        m_gameState = GameState::Paused;
                    } else if (event.key.code == sf::Keyboard::R) {
                        resetGame();
                        spawnNewPiece();
                    }
                    break;
                    
                case GameState::Paused:
                    if (event.key.code == sf::Keyboard::P) {
                        m_gameState = GameState::Playing;
                    } else if (event.key.code == sf::Keyboard::R) {
                        resetGame();
                        m_gameState = GameState::Playing;
                        spawnNewPiece();
                    }
                    break;
                    
                case GameState::GameOver:
                    if (event.key.code == sf::Keyboard::R) {
                        resetGame();
                        m_gameState = GameState::Playing;
                        spawnNewPiece();
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        m_gameState = GameState::Menu;
                    }
                    break;
            }
        }
    }
    
    // Handle continuous input during gameplay
    if (m_gameState == GameState::Playing && m_currentPiece.has_value()) {
        float inputDelay = KEY_REPEAT_DELAY;
        
        // Movement (with repeat)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (isKeyJustPressed(sf::Keyboard::A) || isKeyJustPressed(sf::Keyboard::Left) || 
                m_inputClock.getElapsedTime().asSeconds() > inputDelay) {
                if (tryMovePiece(-1, 0)) {
                    m_inputClock.restart();
                }
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (isKeyJustPressed(sf::Keyboard::D) || isKeyJustPressed(sf::Keyboard::Right) || 
                m_inputClock.getElapsedTime().asSeconds() > inputDelay) {
                if (tryMovePiece(1, 0)) {
                    m_inputClock.restart();
                }
            }
        }
        
        // Soft drop
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (m_inputClock.getElapsedTime().asSeconds() > inputDelay / 4) { // Faster soft drop
                if (tryMovePiece(0, 1)) {
                    m_score++; // Small bonus for soft drop
                    m_inputClock.restart();
                }
            }
        }
        
        // Rotation (no repeat - single press only)
        if (isKeyJustPressed(sf::Keyboard::W) || isKeyJustPressed(sf::Keyboard::Up)) {
            tryRotatePiece();
        }
        
        // Hard drop (no repeat - single press only)
        if (isKeyJustPressed(sf::Keyboard::Space)) {
            m_score += hardDrop();
        }
    }
    
    updateKeyStates();
}

void Game::update(float deltaTime) {
    if (!m_currentPiece.has_value()) {
        return;
    }
    
    // Handle automatic piece dropping
    if (m_dropClock.getElapsedTime().asSeconds() >= m_dropTime) {
        if (!tryMovePiece(0, 1)) {
            // Piece can't move down - place it
            placePieceAndClear();
        }
        m_dropClock.restart();
    }
    
    // Check for game over
    if (m_board.isGameOver()) {
        m_gameState = GameState::GameOver;
    }
}

void Game::render() {
    m_renderer.clear();
    
    switch (m_gameState) {
        case GameState::Menu:
            m_renderer.drawMainMenu();
            break;
            
        case GameState::Playing:
        case GameState::Paused:
            // Draw board and current piece
            m_renderer.drawBoard(m_board);
            
            if (m_currentPiece.has_value()) {
                // Draw ghost piece
                int ghostY = calculateGhostPosition();
                m_renderer.drawGhostPiece(m_currentPiece.value(), ghostY);
                
                // Draw current piece
                m_renderer.drawTetromino(m_currentPiece.value());
            }
            
            // Draw UI
            m_renderer.drawUI(m_score, m_level, m_linesCleared, 
                            m_nextPiece.has_value() ? &m_nextPiece.value() : nullptr);
            
            if (m_gameState == GameState::Paused) {
                m_renderer.drawPauseScreen();
            }
            break;
            
        case GameState::GameOver:
            // Draw final game state
            m_renderer.drawBoard(m_board);
            m_renderer.drawUI(m_score, m_level, m_linesCleared);
            m_renderer.drawGameOver(m_score);
            break;
    }
    
    m_renderer.display();
}

void Game::spawnNewPiece() {
    // Move next piece to current, or create first piece
    if (m_nextPiece.has_value()) {
        m_currentPiece = m_nextPiece.value();
        m_currentPiece->setPosition(BOARD_WIDTH / 2 - 1, 0);
    } else {
        m_currentPiece = Tetromino(getRandomPieceType());
    }
    
    // Generate new next piece
    m_nextPiece = Tetromino(getRandomPieceType());
    
    // Check if the new piece immediately collides (game over condition)
    if (m_board.isCollision(m_currentPiece.value())) {
        m_gameState = GameState::GameOver;
    }
}

TetrominoType Game::getRandomPieceType() {
    return static_cast<TetrominoType>(m_pieceDist(m_rng));
}

bool Game::tryMovePiece(int dx, int dy) {
    if (!m_currentPiece.has_value()) {
        return false;
    }
    
    // Create a copy and try the move
    Tetromino testPiece = m_currentPiece->copy();
    testPiece.move(dx, dy);
    
    if (!m_board.isCollision(testPiece)) {
        m_currentPiece->move(dx, dy);
        return true;
    }
    
    return false;
}

bool Game::tryRotatePiece() {
    if (!m_currentPiece.has_value()) {
        return false;
    }
    
    // Create a copy and try rotation
    Tetromino testPiece = m_currentPiece->copy();
    testPiece.rotate();
    
    if (!m_board.isCollision(testPiece)) {
        m_currentPiece->rotate();
        return true;
    } else {
        // Try wall kicks
        return attemptWallKick(testPiece);
    }
}

int Game::hardDrop() {
    if (!m_currentPiece.has_value()) {
        return 0;
    }
    
    int originalY = m_currentPiece->getPosition().y;
    int dropDistance = 0;
    
    // Move piece down as far as possible
    while (tryMovePiece(0, 1)) {
        dropDistance++;
    }
    
    // Place the piece immediately
    placePieceAndClear();
    
    return dropDistance * 2; // 2 points per row for hard drop
}

int Game::calculateGhostPosition() const {
    if (!m_currentPiece.has_value()) {
        return 0;
    }
    
    Tetromino ghostPiece = m_currentPiece->copy();
    int ghostY = ghostPiece.getPosition().y;
    
    // Move down until collision
    while (true) {
        ghostPiece.move(0, 1);
        if (m_board.isCollision(ghostPiece)) {
            break;
        }
        ghostY++;
    }
    
    return ghostY;
}

void Game::placePieceAndClear() {
    if (!m_currentPiece.has_value()) {
        return;
    }
    
    // Place the piece on the board
    m_board.placePiece(m_currentPiece.value());
    
    // Clear completed lines
    int linesCleared = m_board.clearLines();
    
    // Update score and level
    updateScore(linesCleared);
    
    // Spawn next piece
    spawnNewPiece();
}

void Game::updateScore(int linesCleared, int hardDropLines) {
    // Score for lines cleared (bonus for multiple lines)
    switch (linesCleared) {
        case 1: m_score += 100 * m_level; break;
        case 2: m_score += 300 * m_level; break;
        case 3: m_score += 500 * m_level; break;
        case 4: m_score += 800 * m_level; break; // Tetris bonus
    }
    
    // Add hard drop bonus
    m_score += hardDropLines;
    
    // Update line counts
    m_linesCleared += linesCleared;
    m_linesInCurrentLevel += linesCleared;
    
    // Check for level up
    updateLevel();
}

void Game::updateLevel() {
    if (m_linesInCurrentLevel >= LEVEL_UP_LINES) {
        m_level++;
        m_linesInCurrentLevel = 0;
        m_dropTime = calculateDropTime();
    }
}

float Game::calculateDropTime() const {
    float time = INITIAL_DROP_TIME - (m_level - 1) * DROP_TIME_DECREASE;
    return std::max(time, 0.05f); // Minimum drop time
}

void Game::resetGame() {
    m_board.reset();
    m_score = 0;
    m_level = 1;
    m_linesCleared = 0;
    m_linesInCurrentLevel = 0;
    m_dropTime = INITIAL_DROP_TIME;
    m_currentPiece.reset();
    m_nextPiece.reset();
    m_dropClock.restart();
}

bool Game::isKeyJustPressed(sf::Keyboard::Key key) {
    bool currentState = sf::Keyboard::isKeyPressed(key);
    bool wasPressed = m_keyPressed[key];
    return currentState && !wasPressed;
}

void Game::updateKeyStates() {
    for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
        m_keyPressed[i] = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i));
    }
}

bool Game::attemptWallKick(Tetromino& piece) {
    // Simple wall kick system - try moving left and right
    std::vector<sf::Vector2i> kickOffsets = {{-1, 0}, {1, 0}, {-2, 0}, {2, 0}, {0, -1}};
    
    for (const auto& offset : kickOffsets) {
        Tetromino testPiece = piece.copy();
        testPiece.move(offset.x, offset.y);
        
        if (!m_board.isCollision(testPiece)) {
            // Wall kick successful
            m_currentPiece = testPiece;
            return true;
        }
    }
    
    return false; // No valid wall kick found
}

} // namespace TetrisV2
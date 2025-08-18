/**
 * @file Renderer.cpp
 * @brief Implementation of the Renderer class
 */

#include "TetrisV2/Renderer.h"
#include <iostream>

namespace TetrisV2 {

Renderer::Renderer(sf::RenderWindow& window) 
    : m_window(window), m_fontLoaded(false) {
    
    // Initialize the reusable block shape
    m_blockShape.setSize(sf::Vector2f(BLOCK_SIZE - 1, BLOCK_SIZE - 1)); // -1 for grid lines
    m_blockShape.setOutlineThickness(1.0f);
    m_blockShape.setOutlineColor(GRID_LINE_COLOR);
}

bool Renderer::initialize() {
    // Try to load a default font - on most systems this should work
    if (!m_font.loadFromFile("assets/fonts/arial.ttf")) {
        // If custom font fails, try system default font
        std::cout << "Warning: Could not load assets/fonts/arial.ttf, using default font\n";
        // SFML will use the default system font if no font is loaded
        m_fontLoaded = false;
    } else {
        m_fontLoaded = true;
    }
    
    return true; // Always return true - we can render without custom fonts
}

void Renderer::drawBoard(const Board& board) {
    const auto& grid = board.getGrid();
    
    // Draw background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
    background.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    background.setFillColor(EMPTY_CELL_COLOR);
    m_window.draw(background);
    
    // Draw placed blocks
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            if (grid[y][x] != sf::Color::Transparent) {
                drawBlock(x, y, grid[y][x]);
            }
        }
    }
    
    // Draw grid lines and border
    drawGrid();
    drawBoardBorder();
}

void Renderer::drawTetromino(const Tetromino& tetromino) {
    auto blocks = tetromino.getAbsoluteBlocks();
    sf::Color color = tetromino.getColor();
    
    for (const auto& block : blocks) {
        // Only draw blocks that are within the visible area
        if (block.y >= 0 && block.x >= 0 && block.x < BOARD_WIDTH && block.y < BOARD_HEIGHT) {
            drawBlock(block.x, block.y, color);
        }
    }
}

void Renderer::drawGhostPiece(const Tetromino& tetromino, int ghostY) {
    auto blocks = tetromino.getBlocks();
    sf::Color color = tetromino.getColor();
    color.a = 100; // Make it semi-transparent
    
    for (const auto& block : blocks) {
        int x = tetromino.getPosition().x + block.x;
        int y = ghostY + block.y;
        
        // Only draw blocks that are within the visible area
        if (y >= 0 && x >= 0 && x < BOARD_WIDTH && y < BOARD_HEIGHT) {
            drawBlock(x, y, color, 100);
        }
    }
}

void Renderer::drawText(const std::string& text, sf::Vector2f position, 
                       unsigned int size, sf::Color color) {
    sf::Text textObj;
    if (m_fontLoaded) {
        textObj.setFont(m_font);
    }
    textObj.setString(text);
    textObj.setCharacterSize(size);
    textObj.setFillColor(color);
    textObj.setPosition(position);
    
    m_window.draw(textObj);
}

void Renderer::drawUI(int score, int level, int lines, const Tetromino* nextPiece) {
    // Draw score
    drawText("Score: " + std::to_string(score), 
             sf::Vector2f(UI_PANEL_X, SCORE_Y), 20);
    
    // Draw level
    drawText("Level: " + std::to_string(level), 
             sf::Vector2f(UI_PANEL_X, LEVEL_Y), 20);
    
    // Draw lines cleared
    drawText("Lines: " + std::to_string(lines), 
             sf::Vector2f(UI_PANEL_X, LINES_Y), 20);
    
    // Draw next piece preview if provided
    if (nextPiece) {
        drawText("Next:", sf::Vector2f(UI_PANEL_X, LINES_Y + 50), 20);
        drawNextPiecePreview(*nextPiece, sf::Vector2f(UI_PANEL_X, LINES_Y + 80));
    }
    
    // Draw controls
    drawText("Controls:", sf::Vector2f(UI_PANEL_X, LINES_Y + 200), 16);
    drawText("A/D - Move", sf::Vector2f(UI_PANEL_X, LINES_Y + 225), 14);
    drawText("W - Rotate", sf::Vector2f(UI_PANEL_X, LINES_Y + 245), 14);
    drawText("S - Drop", sf::Vector2f(UI_PANEL_X, LINES_Y + 265), 14);
    drawText("P - Pause", sf::Vector2f(UI_PANEL_X, LINES_Y + 285), 14);
    drawText("R - Restart", sf::Vector2f(UI_PANEL_X, LINES_Y + 305), 14);
}

void Renderer::drawGameOver(int finalScore) {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    m_window.draw(overlay);
    
    // Draw game over text
    sf::Vector2f center(WINDOW_WIDTH / 2.0f - 100, WINDOW_HEIGHT / 2.0f - 50);
    drawText("GAME OVER", center, 36, sf::Color::Red);
    drawText("Final Score: " + std::to_string(finalScore), 
             sf::Vector2f(center.x, center.y + 50), 24);
    drawText("Press R to restart", 
             sf::Vector2f(center.x, center.y + 100), 20);
}

void Renderer::drawPauseScreen() {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    m_window.draw(overlay);
    
    // Draw pause text
    sf::Vector2f center(WINDOW_WIDTH / 2.0f - 70, WINDOW_HEIGHT / 2.0f - 25);
    drawText("PAUSED", center, 36, sf::Color::Yellow);
    drawText("Press P to continue", 
             sf::Vector2f(center.x - 30, center.y + 50), 20);
}

void Renderer::drawMainMenu() {
    sf::Vector2f center(WINDOW_WIDTH / 2.0f - 80, WINDOW_HEIGHT / 2.0f - 100);
    drawText("TETRIS V2", center, 36, sf::Color::Cyan);
    drawText("Press SPACE to start", 
             sf::Vector2f(center.x - 20, center.y + 80), 20);
    drawText("Press ESC to quit", 
             sf::Vector2f(center.x - 10, center.y + 120), 20);
}

void Renderer::clear() {
    m_window.clear(BACKGROUND_COLOR);
}

void Renderer::display() {
    m_window.display();
}

void Renderer::drawBlock(int x, int y, sf::Color color, sf::Uint8 alpha) {
    sf::Vector2f position = gridToScreen(x, y);
    
    color.a = alpha;
    m_blockShape.setFillColor(color);
    m_blockShape.setPosition(position);
    
    m_window.draw(m_blockShape);
}

void Renderer::drawGrid() {
    sf::Color gridColor = GRID_LINE_COLOR;
    gridColor.a = 50; // Make grid lines subtle
    
    // Draw vertical lines
    for (int x = 0; x <= BOARD_WIDTH; x++) {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(1, BOARD_HEIGHT * BLOCK_SIZE));
        line.setPosition(BOARD_OFFSET_X + x * BLOCK_SIZE, BOARD_OFFSET_Y);
        line.setFillColor(gridColor);
        m_window.draw(line);
    }
    
    // Draw horizontal lines
    for (int y = 0; y <= BOARD_HEIGHT; y++) {
        sf::RectangleShape line;
        line.setSize(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, 1));
        line.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y + y * BLOCK_SIZE);
        line.setFillColor(gridColor);
        m_window.draw(line);
    }
}

void Renderer::drawBoardBorder() {
    sf::RectangleShape border;
    border.setSize(sf::Vector2f(BOARD_WIDTH * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE));
    border.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2.0f);
    border.setOutlineColor(sf::Color::White);
    m_window.draw(border);
}

void Renderer::drawNextPiecePreview(const Tetromino& nextPiece, sf::Vector2f position) {
    auto blocks = nextPiece.getBlocks();
    sf::Color color = nextPiece.getColor();
    
    // Create a smaller block for the preview
    sf::RectangleShape previewBlock;
    int previewSize = BLOCK_SIZE / 2;
    previewBlock.setSize(sf::Vector2f(previewSize - 1, previewSize - 1));
    previewBlock.setOutlineThickness(1.0f);
    previewBlock.setOutlineColor(GRID_LINE_COLOR);
    previewBlock.setFillColor(color);
    
    for (const auto& block : blocks) {
        sf::Vector2f blockPos(
            position.x + block.x * previewSize,
            position.y + block.y * previewSize
        );
        previewBlock.setPosition(blockPos);
        m_window.draw(previewBlock);
    }
}

sf::Vector2f Renderer::gridToScreen(int gridX, int gridY) const {
    return sf::Vector2f(
        BOARD_OFFSET_X + gridX * BLOCK_SIZE,
        BOARD_OFFSET_Y + gridY * BLOCK_SIZE
    );
}

} // namespace TetrisV2
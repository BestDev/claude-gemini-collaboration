/**
 * @file Board.cpp
 * @brief Implementation of the Board class
 */

#include "TetrisV2/Board.h"

namespace TetrisV2 {

Board::Board() {
    // Initialize the grid with empty (transparent) cells
    m_grid.resize(BOARD_HEIGHT);
    for (auto& row : m_grid) {
        row.resize(BOARD_WIDTH, sf::Color::Transparent);
    }
}

bool Board::isCollision(const Tetromino& tetromino) const {
    auto blocks = tetromino.getAbsoluteBlocks();
    
    for (const auto& block : blocks) {
        // Check boundaries
        if (block.x < 0 || block.x >= BOARD_WIDTH || block.y >= BOARD_HEIGHT) {
            return true;
        }
        
        // Allow pieces to spawn above the visible area (block.y < 0 is OK)
        if (block.y >= 0 && isCellOccupied(block.x, block.y)) {
            return true;
        }
    }
    
    return false;
}

void Board::placePiece(const Tetromino& tetromino) {
    auto blocks = tetromino.getAbsoluteBlocks();
    sf::Color color = tetromino.getColor();
    
    for (const auto& block : blocks) {
        // Only place blocks that are within the visible board
        if (isValidPosition(block.x, block.y)) {
            m_grid[block.y][block.x] = color;
        }
    }
}

int Board::clearLines() {
    int linesCleared = 0;
    
    // Check each row from bottom to top
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        if (isRowComplete(row)) {
            removeRow(row);
            linesCleared++;
            row++; // Check the same row again since rows above moved down
        }
    }
    
    return linesCleared;
}

const std::vector<std::vector<sf::Color>>& Board::getGrid() const {
    return m_grid;
}

bool Board::isCellOccupied(int x, int y) const {
    if (!isValidPosition(x, y)) {
        return false; // Out of bounds cells are considered unoccupied
    }
    
    return m_grid[y][x] != sf::Color::Transparent;
}

bool Board::isGameOver() const {
    // Game over if the top few rows have any occupied cells where pieces spawn
    int spawnX = BOARD_WIDTH / 2 - 1;
    for (int y = 0; y < 4; y++) { // Check top 4 rows
        for (int x = spawnX - 1; x <= spawnX + 2; x++) { // Check spawn area
            if (isValidPosition(x, y) && isCellOccupied(x, y)) {
                return true;
            }
        }
    }
    return false;
}

void Board::reset() {
    for (auto& row : m_grid) {
        std::fill(row.begin(), row.end(), sf::Color::Transparent);
    }
}

int Board::getHighestBlockRow() const {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (isCellOccupied(col, row)) {
                return row;
            }
        }
    }
    return BOARD_HEIGHT; // No blocks found
}

bool Board::isValidPosition(int x, int y) const {
    return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT;
}

bool Board::isRowComplete(int row) const {
    if (!isValidPosition(0, row)) {
        return false;
    }
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        if (!isCellOccupied(col, row)) {
            return false;
        }
    }
    
    return true;
}

void Board::removeRow(int row) {
    if (!isValidPosition(0, row)) {
        return;
    }
    
    // Remove the row by shifting all rows above it down
    for (int r = row; r > 0; r--) {
        m_grid[r] = m_grid[r - 1];
    }
    
    // Clear the top row
    std::fill(m_grid[0].begin(), m_grid[0].end(), sf::Color::Transparent);
}

void Board::dropRowsAbove(int aboveRow) {
    // This function is now handled by removeRow, but kept for interface completeness
    // Could be used for more complex line clearing algorithms in the future
}

} // namespace TetrisV2
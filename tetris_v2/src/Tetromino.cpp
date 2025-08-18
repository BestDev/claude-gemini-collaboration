/**
 * @file Tetromino.cpp
 * @brief Implementation of the Tetromino class
 */

#include "TetrisV2/Tetromino.h"

namespace TetrisV2 {

Tetromino::Tetromino(TetrominoType type) 
    : m_type(type), m_position(BOARD_WIDTH / 2 - 1, 0), m_rotation(0) {
    initializeShape();
}

void Tetromino::rotate() {
    m_rotation = (m_rotation + 1) % 4;
    initializeShape();
}

void Tetromino::rotateCounterClockwise() {
    m_rotation = (m_rotation + 3) % 4; // +3 is equivalent to -1 in mod 4
    initializeShape();
}

void Tetromino::move(int dx, int dy) {
    m_position.x += dx;
    m_position.y += dy;
}

void Tetromino::setPosition(int x, int y) {
    m_position.x = x;
    m_position.y = y;
}

sf::Vector2i Tetromino::getPosition() const {
    return m_position;
}

const std::vector<sf::Vector2i>& Tetromino::getBlocks() const {
    return m_blocks;
}

std::vector<sf::Vector2i> Tetromino::getAbsoluteBlocks() const {
    std::vector<sf::Vector2i> absoluteBlocks;
    absoluteBlocks.reserve(m_blocks.size());
    
    for (const auto& block : m_blocks) {
        absoluteBlocks.emplace_back(m_position.x + block.x, m_position.y + block.y);
    }
    
    return absoluteBlocks;
}

sf::Color Tetromino::getColor() const {
    return TETROMINO_COLORS[static_cast<int>(m_type)];
}

TetrominoType Tetromino::getType() const {
    return m_type;
}

int Tetromino::getRotation() const {
    return m_rotation;
}

Tetromino Tetromino::copy() const {
    Tetromino copy(m_type);
    copy.m_position = m_position;
    copy.m_rotation = m_rotation;
    copy.m_blocks = m_blocks;
    return copy;
}

void Tetromino::initializeShape() {
    m_blocks = getShapeData(m_type, m_rotation);
}

std::vector<sf::Vector2i> Tetromino::getShapeData(TetrominoType type, int rotation) {
    std::vector<sf::Vector2i> blocks;
    
    switch (type) {
        case TetrominoType::I:
            switch (rotation) {
                case 0: case 2:
                    blocks = {{0, 1}, {1, 1}, {2, 1}, {3, 1}}; // Horizontal
                    break;
                case 1: case 3:
                    blocks = {{2, 0}, {2, 1}, {2, 2}, {2, 3}}; // Vertical
                    break;
            }
            break;
            
        case TetrominoType::O:
            // O piece is the same in all rotations
            blocks = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};
            break;
            
        case TetrominoType::T:
            switch (rotation) {
                case 0:
                    blocks = {{1, 0}, {0, 1}, {1, 1}, {2, 1}}; // T pointing up
                    break;
                case 1:
                    blocks = {{1, 0}, {1, 1}, {2, 1}, {1, 2}}; // T pointing right
                    break;
                case 2:
                    blocks = {{0, 1}, {1, 1}, {2, 1}, {1, 2}}; // T pointing down
                    break;
                case 3:
                    blocks = {{1, 0}, {0, 1}, {1, 1}, {1, 2}}; // T pointing left
                    break;
            }
            break;
            
        case TetrominoType::S:
            switch (rotation) {
                case 0: case 2:
                    blocks = {{1, 0}, {2, 0}, {0, 1}, {1, 1}}; // Horizontal S
                    break;
                case 1: case 3:
                    blocks = {{0, 0}, {0, 1}, {1, 1}, {1, 2}}; // Vertical S
                    break;
            }
            break;
            
        case TetrominoType::Z:
            switch (rotation) {
                case 0: case 2:
                    blocks = {{0, 0}, {1, 0}, {1, 1}, {2, 1}}; // Horizontal Z
                    break;
                case 1: case 3:
                    blocks = {{1, 0}, {0, 1}, {1, 1}, {0, 2}}; // Vertical Z
                    break;
            }
            break;
            
        case TetrominoType::J:
            switch (rotation) {
                case 0:
                    blocks = {{0, 0}, {0, 1}, {1, 1}, {2, 1}}; // J pointing right
                    break;
                case 1:
                    blocks = {{1, 0}, {2, 0}, {1, 1}, {1, 2}}; // J pointing down
                    break;
                case 2:
                    blocks = {{0, 1}, {1, 1}, {2, 1}, {2, 2}}; // J pointing left
                    break;
                case 3:
                    blocks = {{1, 0}, {1, 1}, {1, 2}, {0, 2}}; // J pointing up
                    break;
            }
            break;
            
        case TetrominoType::L:
            switch (rotation) {
                case 0:
                    blocks = {{2, 0}, {0, 1}, {1, 1}, {2, 1}}; // L pointing right
                    break;
                case 1:
                    blocks = {{1, 0}, {1, 1}, {1, 2}, {2, 2}}; // L pointing down
                    break;
                case 2:
                    blocks = {{0, 1}, {1, 1}, {2, 1}, {0, 2}}; // L pointing left
                    break;
                case 3:
                    blocks = {{0, 0}, {1, 0}, {1, 1}, {1, 2}}; // L pointing up
                    break;
            }
            break;
    }
    
    return blocks;
}

} // namespace TetrisV2
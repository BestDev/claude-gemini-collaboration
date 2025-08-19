#include "Tetromino.h"
#include <stdexcept>
#include <random>

namespace Tetris {

// Static member initialization
const std::array<Tetromino::ShapeArray, 7> Tetromino::PIECE_SHAPES = Tetromino::initializePieceShapes();

Tetromino::Tetromino(TetrominoType type, const Position& start_pos)
    : type_(type), position_(start_pos), rotation_(Rotation::NORTH) {
    if (type_ >= TetrominoType::NONE) {
        type_ = TetrominoType::NONE;
    }
}

void Tetromino::rotateClockwise() noexcept {
    rotation_ = static_cast<Rotation>(((static_cast<uint8_t>(rotation_) + 1) % 4));
}

void Tetromino::rotateCounterClockwise() noexcept {
    rotation_ = static_cast<Rotation>(((static_cast<uint8_t>(rotation_) + 3) % 4));
}

const Tetromino::BlockGrid& Tetromino::getCurrentShape() const noexcept {
    if (!isValid()) {
        // Return an empty grid for NONE type
        static const BlockGrid empty_grid{};
        return empty_grid;
    }
    return getShapeArray(type_)[static_cast<size_t>(rotation_)];
}

std::vector<Position> Tetromino::getOccupiedPositions() const {
    return getOccupiedPositions(rotation_);
}

std::vector<Position> Tetromino::getOccupiedPositions(Rotation rot) const {
    if (!isValid()) {
        return {};
    }
    std::vector<Position> positions;
    positions.reserve(4);
    const auto& shape = getShapeArray(type_)[static_cast<size_t>(rot)];
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                positions.emplace_back(x, y);
            }
        }
    }
    return positions;
}

Position Tetromino::getBoundingBox() const noexcept {
    if (!isValid()) {
        return {0, 0};
    }
    int max_x = 0, max_y = 0;
    const auto& shape = getCurrentShape();
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                if (x > max_x) max_x = x;
                if (y > max_y) max_y = y;
            }
        }
    }
    return {max_x + 1, max_y + 1};
}

Tetromino Tetromino::withRotation(Rotation rot) const {
    Tetromino copy = *this;
    copy.rotation_ = rot;
    return copy;
}

Tetromino Tetromino::withPosition(const Position& pos) const {
    Tetromino copy = *this;
    copy.position_ = pos;
    return copy;
}

uint8_t Tetromino::getColorIndex() const noexcept {
    if (!isValid()) {
        return 0; // 0 for empty/none
    }
    // Standard Tetris colors: I=cyan, O=yellow, T=purple, S=green, Z=red, J=blue, L=orange
    static const std::array<uint8_t, 7> colors = {6, 3, 5, 2, 1, 4, 11}; // Using console colors
    return colors[static_cast<size_t>(type_)];
}

void Tetromino::reset() noexcept {
    type_ = TetrominoType::NONE;
    position_ = {0, 0};
    rotation_ = Rotation::NORTH;
}

const Tetromino::ShapeArray& Tetromino::getShapeArray(TetrominoType type) noexcept {
    return PIECE_SHAPES[static_cast<size_t>(type)];
}

// All piece shapes are defined here for all 4 rotations
std::array<Tetromino::ShapeArray, 7> Tetromino::initializePieceShapes() {
    std::array<ShapeArray, 7> shapes{};

    // I piece
    shapes[0][0] = {{ {{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[0][1] = {{ {{0,0,1,0}}, {{0,0,1,0}}, {{0,0,1,0}}, {{0,0,1,0}} }};
    shapes[0][2] = {{ {{0,0,0,0}}, {{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}} }};
    shapes[0][3] = {{ {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}} }};

    // O piece (all rotations are the same)
    shapes[1][0] = {{ {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[1][1] = shapes[1][0];
    shapes[1][2] = shapes[1][0];
    shapes[1][3] = shapes[1][0];

    // T piece
    shapes[2][0] = {{ {{0,1,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[2][1] = {{ {{0,1,0,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};
    shapes[2][2] = {{ {{0,0,0,0}}, {{1,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};
    shapes[2][3] = {{ {{0,1,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};

    // S piece
    shapes[3][0] = {{ {{0,1,1,0}}, {{1,1,0,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[3][1] = {{ {{0,1,0,0}}, {{0,1,1,0}}, {{0,0,1,0}}, {{0,0,0,0}} }};
    shapes[3][2] = {{ {{0,0,0,0}}, {{0,1,1,0}}, {{1,1,0,0}}, {{0,0,0,0}} }};
    shapes[3][3] = {{ {{1,0,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};

    // Z piece
    shapes[4][0] = {{ {{1,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[4][1] = {{ {{0,0,1,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};
    shapes[4][2] = {{ {{0,0,0,0}}, {{1,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}} }};
    shapes[4][3] = {{ {{0,1,0,0}}, {{1,1,0,0}}, {{1,0,0,0}}, {{0,0,0,0}} }};

    // J piece
    shapes[5][0] = {{ {{1,0,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[5][1] = {{ {{0,1,1,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};
    shapes[5][2] = {{ {{0,0,0,0}}, {{1,1,1,0}}, {{0,0,1,0}}, {{0,0,0,0}} }};
    shapes[5][3] = {{ {{0,1,0,0}}, {{0,1,0,0}}, {{1,1,0,0}}, {{0,0,0,0}} }};

    // L piece
    shapes[6][0] = {{ {{0,0,1,0}}, {{1,1,1,0}}, {{0,0,0,0}}, {{0,0,0,0}} }};
    shapes[6][1] = {{ {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}} }};
    shapes[6][2] = {{ {{0,0,0,0}}, {{1,1,1,0}}, {{1,0,0,0}}, {{0,0,0,0}} }};
    shapes[6][3] = {{ {{1,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,0,0,0}} }};

    return shapes;
}

Tetromino createRandomTetromino(const Position& pos) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> distrib(0, 6);
    return Tetromino(static_cast<TetrominoType>(distrib(gen)), pos);
}

Tetromino createTetromino(TetrominoType type, const Position& pos) {
    return Tetromino(type, pos);
}

} // namespace Tetris

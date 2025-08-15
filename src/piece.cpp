#include "piece.h"
#include <random>
#include <chrono>

namespace tetris {

// 7가지 테트로미노 데이터 정의
const std::array<std::array<std::array<std::array<bool, 4>, 4>, 4>, 7> Piece::piece_data_ = Piece::initializePieceData();

std::array<std::array<std::array<std::array<bool, 4>, 4>, 4>, 7> Piece::initializePieceData() noexcept {
    std::array<std::array<std::array<std::array<bool, 4>, 4>, 4>, 7> data{};
    
    // I 조각
    data[0][0] = {{{{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}}, {{0,0,0,0}}}};
    data[0][1] = {{{{0,0,1,0}}, {{0,0,1,0}}, {{0,0,1,0}}, {{0,0,1,0}}}};
    data[0][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{1,1,1,1}}, {{0,0,0,0}}}};
    data[0][3] = {{{{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}}};
    
    // O 조각
    data[1][0] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}};
    data[1][1] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}};
    data[1][2] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}};
    data[1][3] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,1,0}}, {{0,0,0,0}}}};
    
    // T 조각
    data[2][0] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}}};
    data[2][1] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{0,1,1,0}}, {{0,1,0,0}}}};
    data[2][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{1,1,1,0}}, {{0,1,0,0}}}};
    data[2][3] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}}};
    
    // S 조각
    data[3][0] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{1,1,0,0}}, {{0,0,0,0}}}};
    data[3][1] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{0,1,1,0}}, {{0,0,1,0}}}};
    data[3][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{0,1,1,0}}, {{1,1,0,0}}}};
    data[3][3] = {{{{0,0,0,0}}, {{1,0,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}}};
    
    // Z 조각
    data[4][0] = {{{{0,0,0,0}}, {{1,1,0,0}}, {{0,1,1,0}}, {{0,0,0,0}}}};
    data[4][1] = {{{{0,0,0,0}}, {{0,0,1,0}}, {{0,1,1,0}}, {{0,1,0,0}}}};
    data[4][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{1,1,0,0}}, {{0,1,1,0}}}};
    data[4][3] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{1,1,0,0}}, {{1,0,0,0}}}};
    
    // J 조각
    data[5][0] = {{{{0,0,0,0}}, {{1,0,0,0}}, {{1,1,1,0}}, {{0,0,0,0}}}};
    data[5][1] = {{{{0,0,0,0}}, {{0,1,1,0}}, {{0,1,0,0}}, {{0,1,0,0}}}};
    data[5][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{1,1,1,0}}, {{0,0,1,0}}}};
    data[5][3] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{1,1,0,0}}}};
    
    // L 조각
    data[6][0] = {{{{0,0,0,0}}, {{0,0,1,0}}, {{1,1,1,0}}, {{0,0,0,0}}}};
    data[6][1] = {{{{0,0,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}, {{0,1,1,0}}}};
    data[6][2] = {{{{0,0,0,0}}, {{0,0,0,0}}, {{1,1,1,0}}, {{1,0,0,0}}}};
    data[6][3] = {{{{0,0,0,0}}, {{1,1,0,0}}, {{0,1,0,0}}, {{0,1,0,0}}}};
    
    return data;
}

Piece::Piece() noexcept : type_(PieceType::EMPTY), position_(0, 0), rotation_state_(0) {}

Piece::Piece(PieceType type, const Position& start_pos) noexcept 
    : type_(type), position_(start_pos), rotation_state_(0) {}

void Piece::setPosition(const Position& new_pos) noexcept {
    position_ = new_pos;
}

void Piece::move(const Position& offset) noexcept {
    position_ += offset;
}

void Piece::moveLeft() noexcept {
    position_.x--;
}

void Piece::moveRight() noexcept {
    position_.x++;
}

void Piece::moveDown() noexcept {
    position_.y++;
}

bool Piece::rotate(RotationDirection direction) noexcept {
    if (direction == RotationDirection::CLOCKWISE) {
        rotation_state_ = (rotation_state_ + 1) % NUM_ROTATIONS;
    } else {
        rotation_state_ = (rotation_state_ + NUM_ROTATIONS - 1) % NUM_ROTATIONS;
    }
    return true;
}

std::vector<Position> Piece::getBlockPositions() const {
    std::vector<Position> positions;
    
    if (type_ == PieceType::EMPTY) return positions;
    
    const auto& shape = piece_data_[static_cast<int>(type_)][rotation_state_];
    
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (shape[row][col]) {
                positions.emplace_back(position_.x + col, position_.y + row);
            }
        }
    }
    
    return positions;
}

const std::array<std::array<bool, 4>, 4>& Piece::getShape() const noexcept {
    static const std::array<std::array<bool, 4>, 4> empty_shape = {};
    
    if (type_ == PieceType::EMPTY) {
        return empty_shape;
    }
    
    return piece_data_[static_cast<int>(type_)][rotation_state_];
}

bool Piece::hasBlockAt(int rel_x, int rel_y) const noexcept {
    if (rel_x < 0 || rel_x >= PIECE_SIZE || rel_y < 0 || rel_y >= PIECE_SIZE) {
        return false;
    }
    
    if (type_ == PieceType::EMPTY) {
        return false;
    }
    
    return piece_data_[static_cast<int>(type_)][rotation_state_][rel_y][rel_x];
}

void Piece::reset(PieceType type, const Position& start_pos) noexcept {
    type_ = type;
    position_ = start_pos;
    rotation_state_ = 0;
}

std::array<int, 4> Piece::getBoundingBox() const noexcept {
    if (type_ == PieceType::EMPTY) {
        return {{0, 0, 0, 0}};
    }
    
    int min_x = PIECE_SIZE, min_y = PIECE_SIZE;
    int max_x = -1, max_y = -1;
    
    const auto& shape = piece_data_[static_cast<int>(type_)][rotation_state_];
    
    for (int row = 0; row < PIECE_SIZE; row++) {
        for (int col = 0; col < PIECE_SIZE; col++) {
            if (shape[row][col]) {
                min_x = std::min(min_x, col);
                max_x = std::max(max_x, col);
                min_y = std::min(min_y, row);
                max_y = std::max(max_y, row);
            }
        }
    }
    
    return {{min_x, min_y, max_x, max_y}};
}

PieceType Piece::generateRandomType() noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 6);
    
    return static_cast<PieceType>(dis(gen));
}

char Piece::typeToChar(PieceType type) noexcept {
    switch (type) {
        case PieceType::I: return 'I';
        case PieceType::O: return 'O';
        case PieceType::T: return 'T';
        case PieceType::S: return 'S';
        case PieceType::Z: return 'Z';
        case PieceType::J: return 'J';
        case PieceType::L: return 'L';
        case PieceType::EMPTY: return ' ';
        default: return '?';
    }
}

int Piece::getColorIndex(PieceType type) noexcept {
    switch (type) {
        case PieceType::I: return 1; // 청록색
        case PieceType::O: return 2; // 노란색
        case PieceType::T: return 3; // 보라색
        case PieceType::S: return 4; // 초록색
        case PieceType::Z: return 5; // 빨간색
        case PieceType::J: return 6; // 파란색
        case PieceType::L: return 7; // 주황색
        default: return 0;
    }
}

} // namespace tetris
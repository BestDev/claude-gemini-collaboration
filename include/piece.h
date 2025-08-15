#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include <vector>
#include <array>
#include <memory>

namespace tetris {

enum class PieceType : int {
    I = 0,  // 일직선 조각
    O = 1,  // 정사각형 조각  
    T = 2,  // T자 조각
    J = 3,  // J자 조각
    L = 4,  // L자 조각
    S = 5,  // S자 조각
    Z = 6,  // Z자 조각
    EMPTY = -1  // 빈 공간
};

struct Position {
    int x;
    int y;
    
    Position() noexcept : x(0), y(0) {}
    Position(int x_val, int y_val) noexcept : x(x_val), y(y_val) {}
    
    Position& operator+=(const Position& other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Position operator+(const Position& other) const noexcept {
        return Position(x + other.x, y + other.y);
    }
    
    bool operator==(const Position& other) const noexcept {
        return x == other.x && y == other.y;
    }
};

enum class RotationDirection {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

class Piece {
private:
    static constexpr int PIECE_SIZE = 4;
    static constexpr int NUM_ROTATIONS = 4;
    
    PieceType type_;
    Position position_;
    int rotation_state_;
    
    static const std::array<std::array<std::array<std::array<bool, PIECE_SIZE>, PIECE_SIZE>, NUM_ROTATIONS>, 7> piece_data_;
    
public:
    Piece() noexcept;
    explicit Piece(PieceType type, const Position& start_pos = Position(0, 0)) noexcept;
    
    Piece(const Piece& other) noexcept = default;
    Piece(Piece&& other) noexcept = default;
    Piece& operator=(const Piece& other) noexcept = default;
    Piece& operator=(Piece&& other) noexcept = default;
    ~Piece() noexcept = default;
    
    // 접근자 메서드
    PieceType getType() const noexcept { return type_; }
    const Position& getPosition() const noexcept { return position_; }
    int getRotationState() const noexcept { return rotation_state_; }
    
    // 조작 메서드
    void setPosition(const Position& new_pos) noexcept;
    void move(const Position& offset) noexcept;
    void moveLeft() noexcept;
    void moveRight() noexcept;
    void moveDown() noexcept;
    bool rotate(RotationDirection direction = RotationDirection::CLOCKWISE) noexcept;
    
    // 형태 정보 메서드
    std::vector<Position> getBlockPositions() const;
    const std::array<std::array<bool, PIECE_SIZE>, PIECE_SIZE>& getShape() const noexcept;
    bool hasBlockAt(int rel_x, int rel_y) const noexcept;
    
    // 유틸리티 메서드
    bool isValid() const noexcept { return type_ != PieceType::EMPTY; }
    void reset(PieceType type = PieceType::EMPTY, const Position& start_pos = Position(0, 0)) noexcept;
    std::array<int, 4> getBoundingBox() const noexcept;
    
    // 정적 유틸리티 메서드
    static PieceType generateRandomType() noexcept;
    static char typeToChar(PieceType type) noexcept;
    static int getColorIndex(PieceType type) noexcept;

private:
    static std::array<std::array<std::array<std::array<bool, PIECE_SIZE>, PIECE_SIZE>, NUM_ROTATIONS>, 7> initializePieceData() noexcept;
};

inline bool operator==(const Piece& lhs, const Piece& rhs) noexcept {
    return lhs.getType() == rhs.getType() && 
           lhs.getPosition() == rhs.getPosition() && 
           lhs.getRotationState() == rhs.getRotationState();
}

inline bool operator!=(const Piece& lhs, const Piece& rhs) noexcept {
    return !(lhs == rhs);
}

} // namespace tetris

#endif // TETRIS_PIECE_H
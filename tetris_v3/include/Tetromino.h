#pragma once

#include <array>
#include <vector>
#include <cstdint>

namespace Tetris {

/**
 * @brief Enumeration of the seven standard Tetris piece types
 */
enum class TetrominoType : uint8_t {
    I = 0,  // Line piece
    O = 1,  // Square piece
    T = 2,  // T-shaped piece
    S = 3,  // S-shaped piece
    Z = 4,  // Z-shaped piece
    J = 5,  // J-shaped piece
    L = 6,  // L-shaped piece
    NONE = 7
};

/**
 * @brief 2D position structure
 */
struct Position {
    int x{0};
    int y{0};
    
    Position() = default;
    Position(int x_pos, int y_pos) : x(x_pos), y(y_pos) {}
    
    Position operator+(const Position& other) const {
        return {x + other.x, y + other.y};
    }
    
    Position& operator+=(const Position& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

/**
 * @brief Rotation state enumeration
 */
enum class Rotation : uint8_t {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

/**
 * @brief Tetromino class representing a falling piece in Tetris
 * 
 * This class manages the shape, position, and rotation of Tetris pieces.
 * Uses data-oriented design for optimal cache performance and supports
 * all standard Tetris piece mechanics including SRS (Super Rotation System).
 */
class Tetromino {
public:
    // Each piece is defined as a 4x4 grid of blocks
    using BlockGrid = std::array<std::array<bool, 4>, 4>;
    using ShapeArray = std::array<BlockGrid, 4>; // 4 rotation states
    
    /**
     * @brief Construct a Tetromino with specified type and position
     * @param type The type of Tetromino piece
     * @param start_pos Initial position on the board
     */
    explicit Tetromino(TetrominoType type, const Position& start_pos = {0, 0});
    
    /**
     * @brief Default constructor creates an empty piece
     */
    Tetromino() = default;
    
    // Copy and move semantics
    Tetromino(const Tetromino&) = default;
    Tetromino& operator=(const Tetromino&) = default;
    Tetromino(Tetromino&&) = default;
    Tetromino& operator=(Tetromino&&) = default;
    
    /**
     * @brief Get the current piece type
     * @return The TetrominoType of this piece
     */
    [[nodiscard]] TetrominoType getType() const noexcept { return type_; }
    
    /**
     * @brief Get the current position
     * @return Current position of the piece
     */
    [[nodiscard]] const Position& getPosition() const noexcept { return position_; }
    
    /**
     * @brief Get the current rotation state
     * @return Current rotation of the piece
     */
    [[nodiscard]] Rotation getRotation() const noexcept { return rotation_; }
    
    /**
     * @brief Set the position of the piece
     * @param pos New position
     */
    void setPosition(const Position& pos) noexcept { position_ = pos; }
    
    /**
     * @brief Move the piece by the specified offset
     * @param offset Movement offset
     */
    void move(const Position& offset) noexcept { position_ += offset; }
    
    /**
     * @brief Rotate the piece clockwise
     */
    void rotateClockwise() noexcept;
    
    /**
     * @brief Rotate the piece counter-clockwise
     */
    void rotateCounterClockwise() noexcept;
    
    /**
     * @brief Get the current shape grid
     * @return 4x4 grid representing the current piece shape
     */
    [[nodiscard]] const BlockGrid& getCurrentShape() const noexcept;
    
    /**
     * @brief Get occupied positions relative to piece position
     * @return Vector of positions occupied by this piece
     */
    [[nodiscard]] std::vector<Position> getOccupiedPositions() const;
    
    /**
     * @brief Get occupied positions for a specific rotation
     * @param rot The rotation to check
     * @return Vector of positions occupied by this piece at the given rotation
     */
    [[nodiscard]] std::vector<Position> getOccupiedPositions(Rotation rot) const;
    
    /**
     * @brief Check if the piece is valid (not empty)
     * @return True if piece has a valid type
     */
    [[nodiscard]] bool isValid() const noexcept { return type_ != TetrominoType::NONE; }
    
    /**
     * @brief Get the bounding box size of the current piece
     * @return Position representing width (x) and height (y) of bounding box
     */
    [[nodiscard]] Position getBoundingBox() const noexcept;
    
    /**
     * @brief Create a copy of this piece with a different rotation
     * @param rot The desired rotation
     * @return New Tetromino with the specified rotation
     */
    [[nodiscard]] Tetromino withRotation(Rotation rot) const;
    
    /**
     * @brief Create a copy of this piece at a different position
     * @param pos The desired position
     * @return New Tetromino at the specified position
     */
    [[nodiscard]] Tetromino withPosition(const Position& pos) const;
    
    /**
     * @brief Get the color index for this piece type (for rendering)
     * @return Color index (1-7) for this piece type
     */
    [[nodiscard]] uint8_t getColorIndex() const noexcept;
    
    /**
     * @brief Reset to empty state
     */
    void reset() noexcept;

private:
    TetrominoType type_{TetrominoType::NONE};
    Position position_{0, 0};
    Rotation rotation_{Rotation::NORTH};
    
    // Static shape definitions for all piece types and rotations
    static const std::array<ShapeArray, 7> PIECE_SHAPES;
    
    /**
     * @brief Initialize shape data for all piece types
     * @return Array of shape definitions
     */
    static std::array<ShapeArray, 7> initializePieceShapes();
    
    /**
     * @brief Get shape array for a specific piece type
     * @param type The piece type
     * @return Reference to the shape array for that type
     */
    [[nodiscard]] static const ShapeArray& getShapeArray(TetrominoType type) noexcept;
};

/**
 * @brief Factory function to create a random Tetromino
 * @param pos Starting position for the piece
 * @return Randomly generated Tetromino
 */
[[nodiscard]] Tetromino createRandomTetromino(const Position& pos = {0, 0});

/**
 * @brief Factory function to create a specific Tetromino type
 * @param type The type of piece to create
 * @param pos Starting position for the piece
 * @return Tetromino of the specified type
 */
[[nodiscard]] Tetromino createTetromino(TetrominoType type, const Position& pos = {0, 0});

} // namespace Tetris
#include "Board.h"
#include <algorithm>
#include <stdexcept>

namespace Tetris {

Board::Board() {
    clear();
}

void Board::clear() noexcept {
    for (auto& row : grid_) {
        for (auto& cell : row) {
            cell.clear();
        }
    }
}

void Board::reset() noexcept {
    clear();
}

bool Board::isValidPosition(const Position& pos) const noexcept {
    return isInBounds(pos.x, pos.y);
}

bool Board::isEmpty(const Position& pos) const noexcept {
    return isInBounds(pos.x, pos.y) && grid_[pos.y][pos.x].isEmpty();
}

bool Board::isOccupied(const Position& pos) const noexcept {
    return isInBounds(pos.x, pos.y) && grid_[pos.y][pos.x].occupied;
}

const Cell& Board::getCell(const Position& pos) const {
    if (!isInBounds(pos.x, pos.y)) throw std::out_of_range("Board position out of range");
    return grid_[pos.y][pos.x];
}

Cell& Board::getCell(const Position& pos) {
    if (!isInBounds(pos.x, pos.y)) throw std::out_of_range("Board position out of range");
    return grid_[pos.y][pos.x];
}

const Cell& Board::getCell(int x, int y) const {
    if (!isInBounds(x, y)) throw std::out_of_range("Board position out of range");
    return grid_[y][x];
}

bool Board::canPlacePiece(const Tetromino& piece) const {
    return canPlacePiece(piece, piece.getPosition(), piece.getRotation());
}

bool Board::canPlacePiece(const Tetromino& piece, const Position& pos, Rotation rot) const {
    if (!piece.isValid()) return false;
    auto piece_positions = getPiecePositions(piece, pos, rot);
    for (const auto& p : piece_positions) {
        if (!isInBounds(p.x, p.y) || isOccupied(p)) {
            return false;
        }
    }
    return true;
}

bool Board::placePiece(const Tetromino& piece) {
    if (!canPlacePiece(piece)) {
        return false;
    }
    
    const auto& piece_pos = piece.getPosition();
    const auto& shape = piece.getCurrentShape();
    const uint8_t color = piece.getColorIndex();

    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                Position board_pos = {piece_pos.x + x, piece_pos.y + y};
                if (isInBounds(board_pos.x, board_pos.y)) {
                    grid_[board_pos.y][board_pos.x].set(color);
                }
            }
        }
    }
    return true;
}

int Board::clearLines() {
    int cleared_lines = 0;
    for (int y = HEIGHT - 1; y >= 0; --y) {
        if (isLineComplete(y)) {
            removeLine(y);
            cleared_lines++;
            y++; // Re-check the same line index as it's now new content
        }
    }
    
    if (cleared_lines > 0 && line_clear_callback_) {
        // In a real game, level would be passed here.
        // For now, we pass a placeholder level 1.
        line_clear_callback_(cleared_lines, 1);
    }
    
    return cleared_lines;
}

bool Board::isLineComplete(int line) const {
    if (line < 0 || line >= HEIGHT) return false;
    for (int x = 0; x < WIDTH; ++x) {
        if (grid_[line][x].isEmpty()) {
            return false;
        }
    }
    return true;
}

void Board::removeLine(int line) {
    if (line < 0 || line >= HEIGHT) return;
    
    for (int y = line; y > 0; --y) {
        grid_[y] = grid_[y - 1];
    }
    // Clear the top line
    grid_[0].fill(Cell());
}

bool Board::isGameOver() const {
    // Game is over if any cell in the top row (or just outside, in the spawn zone) is occupied.
    for (int x = 0; x < WIDTH; ++x) {
        if (isOccupied({x, 0})) {
            return true;
        }
    }
    return false;
}

Position Board::findDropPosition(const Tetromino& piece) const {
    Position drop_pos = piece.getPosition();
    while (canPlacePiece(piece, {drop_pos.x, drop_pos.y + 1}, piece.getRotation())) {
        drop_pos.y++;
    }
    return drop_pos;
}

Board Board::getPreviewBoard(const Tetromino& piece, uint8_t ghost_color) const {
    Board preview = *this;
    Position ghost_pos = findDropPosition(piece);
    Tetromino ghost_piece = piece.withPosition(ghost_pos);
    
    const auto& shape = ghost_piece.getCurrentShape();
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                Position board_pos = {ghost_pos.x + x, ghost_pos.y + y};
                if (preview.isInBounds(board_pos.x, board_pos.y) && preview.isEmpty(board_pos)) {
                    preview.getCell(board_pos).set(ghost_color);
                }
            }
        }
    }
    return preview;
}

int Board::countCompleteLines() const {
    int count = 0;
    for (int y = 0; y < HEIGHT; ++y) {
        if (isLineComplete(y)) {
            count++;
        }
    }
    return count;
}

std::vector<int> Board::getCompleteLines() const {
    std::vector<int> lines;
    for (int y = 0; y < HEIGHT; ++y) {
        if (isLineComplete(y)) {
            lines.push_back(y);
        }
    }
    return lines;
}

int Board::getColumnHeight(int column) const {
    if (column < 0 || column >= WIDTH) return 0;
    for (int y = 0; y < HEIGHT; ++y) {
        if (grid_[y][column].occupied) {
            return HEIGHT - y;
        }
    }
    return 0;
}

Board::BoardStats Board::calculateStats() const {
    BoardStats stats;
    stats.complete_lines = countCompleteLines();
    
    std::array<int, WIDTH> heights;
    for (int x = 0; x < WIDTH; ++x) {
        heights[x] = getColumnHeight(x);
        stats.total_height += heights[x];
        if (heights[x] > stats.max_height) {
            stats.max_height = heights[x];
        }
        
        // Calculate holes
        for (int y = HEIGHT - heights[x]; y < HEIGHT; ++y) {
            if (grid_[y][x].isEmpty()) {
                stats.holes++;
            }
        }
    }
    
    // Calculate bumpiness
    for (int x = 0; x < WIDTH - 1; ++x) {
        stats.bumpiness += std::abs(heights[x] - heights[x+1]);
    }
    
    return stats;
}

std::vector<Position> Board::getPiecePositions(const Tetromino& piece, const Position& pos, Rotation rot) const {
    std::vector<Position> positions;
    positions.reserve(4);
    auto temp_piece = piece.withRotation(rot);
    const auto& shape = temp_piece.getCurrentShape();
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (shape[y][x]) {
                positions.push_back({pos.x + x, pos.y + y});
            }
        }
    }
    return positions;
}

Board createStandardBoard() {
    return Board();
}

} // namespace Tetris

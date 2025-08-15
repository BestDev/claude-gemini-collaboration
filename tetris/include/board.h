#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "piece.h"
#include <vector>
#include <array>
#include <memory>
#include <functional>

namespace tetris {

enum class GameState {
    PLAYING,
    PAUSED,
    GAME_OVER,
    LINE_CLEAR_ANIMATION
};

enum class GameEvent {
    LINE_CLEARED,
    PIECE_LANDED,
    PIECE_SPAWNED,
    GAME_OVER,
    LEVEL_UP
};

class Board {
public:
    static constexpr int BOARD_WIDTH = 10;
    static constexpr int BOARD_HEIGHT = 20;
    static constexpr int VISIBLE_HEIGHT = 20;
    static constexpr int SPAWN_X = BOARD_WIDTH / 2 - 2;
    static constexpr int SPAWN_Y = 0;
    
    // 점수 계산 상수
    static constexpr int SCORE_SINGLE = 100;
    static constexpr int SCORE_DOUBLE = 300;
    static constexpr int SCORE_TRIPLE = 500;
    static constexpr int SCORE_TETRIS = 800;
    static constexpr int SCORE_SOFT_DROP = 1;
    static constexpr int SCORE_HARD_DROP = 2;
    
private:
    std::array<std::array<PieceType, BOARD_WIDTH>, BOARD_HEIGHT> grid_;
    std::unique_ptr<Piece> current_piece_;
    std::unique_ptr<Piece> next_piece_;
    std::unique_ptr<Piece> hold_piece_;
    
    GameState state_;
    bool hold_used_;
    
    unsigned long score_;
    int level_;
    int lines_cleared_;
    
    std::function<void(GameEvent, int)> event_callback_;
    
public:
    Board() noexcept;
    ~Board() noexcept = default;
    
    // 복사/이동 제한
    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(Board&&) = delete;
    
    // 게임 초기화 및 제어
    void initialize() noexcept;
    void reset() noexcept;
    void setState(GameState state) noexcept { state_ = state; }
    GameState getState() const noexcept { return state_; }
    
    // 조각 관리
    bool spawnNewPiece() noexcept;
    bool moveCurrentPieceLeft() noexcept;
    bool moveCurrentPieceRight() noexcept;
    bool moveCurrentPieceDown() noexcept;
    bool rotateCurrentPiece(RotationDirection direction = RotationDirection::CLOCKWISE) noexcept;
    int hardDropCurrentPiece() noexcept;
    bool holdCurrentPiece() noexcept;
    
    // 충돌 검사
    bool isValidPosition(const Piece& piece) const noexcept;
    bool canPlacePieceAt(const Piece& piece, const Position& pos) const noexcept;
    bool isCurrentPieceLanded() const noexcept;
    
    // 보드 조작
    void lockCurrentPiece() noexcept;
    int clearCompletedLines() noexcept;
    bool isLineComplete(int row) const noexcept;
    void removeLine(int row) noexcept;
    
    // 접근자 메서드
    PieceType getCellType(int x, int y) const noexcept;
    const Piece* getCurrentPiece() const noexcept { return current_piece_.get(); }
    const Piece* getNextPiece() const noexcept { return next_piece_.get(); }
    const Piece* getHoldPiece() const noexcept { return hold_piece_.get(); }
    unsigned long getScore() const noexcept { return score_; }
    int getLevel() const noexcept { return level_; }
    int getLinesCleared() const noexcept { return lines_cleared_; }
    
    // 점수 및 레벨 관리
    void addScore(unsigned long points) noexcept;
    int getDropInterval() const noexcept;
    
    // 유틸리티 메서드
    Piece calculateGhostPiece() const noexcept;
    bool isGameOver() const noexcept;
    int getBoardHeight() const noexcept;
    int countHoles() const noexcept;
    void setEventCallback(std::function<void(GameEvent, int)> callback) noexcept {
        event_callback_ = std::move(callback);
    }
    
    // 화면 출력 (ncurses)
    void draw(int start_x, int start_y, bool show_ghost = true) const noexcept;
    void drawNextPiece(int start_x, int start_y) const noexcept;
    void drawHoldPiece(int start_x, int start_y) const noexcept;
    void drawGameInfo(int start_x, int start_y) const noexcept;

private:
    void clearGrid() noexcept;
    void updateLevel() noexcept;
    void triggerEvent(GameEvent event, int value = 0) noexcept;
    Piece tryWallKick(const Piece& piece, RotationDirection direction) const noexcept;
    void drawCell(int x, int y, PieceType type, bool is_ghost = false) const noexcept;
};

} // namespace tetris

#endif // TETRIS_BOARD_H
#include "board.h"
#include <ncurses.h>
#include <algorithm>
#include <cstring>

namespace tetris {

Board::Board() noexcept 
    : state_(GameState::PLAYING), hold_used_(false), score_(0), level_(1), lines_cleared_(0) {
    clearGrid();
}

void Board::initialize() noexcept {
    clearGrid();
    state_ = GameState::PLAYING;
    hold_used_ = false;
    score_ = 0;
    level_ = 1;
    lines_cleared_ = 0;
    
    current_piece_.reset();
    next_piece_.reset();
    hold_piece_.reset();
    
    spawnNewPiece();
}

void Board::reset() noexcept {
    initialize();
}

bool Board::spawnNewPiece() noexcept {
    // 다음 조각이 없으면 새로 생성
    if (!next_piece_) {
        next_piece_.reset(new Piece(Piece::generateRandomType(), Position(SPAWN_X, SPAWN_Y)));
    }
    
    // 현재 조각을 다음 조각으로 교체
    current_piece_ = std::move(next_piece_);
    next_piece_.reset(new Piece(Piece::generateRandomType(), Position(SPAWN_X, SPAWN_Y)));
    
    // 새 조각을 스폰 위치에 배치할 수 있는지 확인
    if (!isValidPosition(*current_piece_)) {
        state_ = GameState::GAME_OVER;
        triggerEvent(GameEvent::GAME_OVER);
        return false;
    }
    
    hold_used_ = false;
    triggerEvent(GameEvent::PIECE_SPAWNED);
    return true;
}

bool Board::moveCurrentPieceLeft() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveLeft();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveLeft();
        return true;
    }
    return false;
}

bool Board::moveCurrentPieceRight() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveRight();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveRight();
        return true;
    }
    return false;
}

bool Board::moveCurrentPieceDown() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveDown();
    
    if (isValidPosition(test_piece)) {
        current_piece_->moveDown();
        addScore(SCORE_SOFT_DROP);
        return true;
    }
    return false;
}

bool Board::rotateCurrentPiece(RotationDirection direction) noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.rotate(direction);
    
    // Wall kick 시도
    Piece kicked_piece = tryWallKick(test_piece, direction);
    
    if (isValidPosition(kicked_piece)) {
        *current_piece_ = kicked_piece;
        return true;
    }
    return false;
}

int Board::hardDropCurrentPiece() noexcept {
    if (!current_piece_ || state_ != GameState::PLAYING) return 0;
    
    int drop_distance = 0;
    while (moveCurrentPieceDown()) {
        drop_distance++;
    }
    
    addScore(drop_distance * SCORE_HARD_DROP);
    return drop_distance;
}

bool Board::holdCurrentPiece() noexcept {
    if (!current_piece_ || hold_used_ || state_ != GameState::PLAYING) return false;
    
    if (!hold_piece_) {
        // 처음 홀드하는 경우
        hold_piece_ = std::move(current_piece_);
        hold_piece_->setPosition(Position(0, 0));
        spawnNewPiece();
    } else {
        // 기존 홀드 조각과 교체
        std::swap(current_piece_, hold_piece_);
        current_piece_->setPosition(Position(SPAWN_X, SPAWN_Y));
        
        if (!isValidPosition(*current_piece_)) {
            return false; // 홀드 조각을 배치할 수 없음
        }
    }
    
    hold_used_ = true;
    return true;
}

bool Board::isValidPosition(const Piece& piece) const noexcept {
    auto positions = piece.getBlockPositions();
    
    for (const auto& pos : positions) {
        // 보드 경계 체크
        if (pos.x < 0 || pos.x >= BOARD_WIDTH || pos.y >= BOARD_HEIGHT) {
            return false;
        }
        
        // 위쪽 경계는 조금 여유를 둠 (조각이 위에서 나타날 수 있도록)
        if (pos.y < 0) continue;
        
        // 기존 블록과 충돌 체크
        if (grid_[pos.y][pos.x] != PieceType::EMPTY) {
            return false;
        }
    }
    
    return true;
}

bool Board::canPlacePieceAt(const Piece& piece, const Position& pos) const noexcept {
    Piece test_piece = piece;
    test_piece.setPosition(pos);
    return isValidPosition(test_piece);
}

bool Board::isCurrentPieceLanded() const noexcept {
    if (!current_piece_) return false;
    
    Piece test_piece = *current_piece_;
    test_piece.moveDown();
    
    return !isValidPosition(test_piece);
}

void Board::lockCurrentPiece() noexcept {
    if (!current_piece_) return;
    
    auto positions = current_piece_->getBlockPositions();
    for (const auto& pos : positions) {
        if (pos.y >= 0 && pos.y < BOARD_HEIGHT && pos.x >= 0 && pos.x < BOARD_WIDTH) {
            grid_[pos.y][pos.x] = current_piece_->getType();
        }
    }
    
    triggerEvent(GameEvent::PIECE_LANDED);
    
    // 줄 제거 확인
    int cleared = clearCompletedLines();
    if (cleared > 0) {
        triggerEvent(GameEvent::LINE_CLEARED, cleared);
    }
    
    // 새 조각 생성
    spawnNewPiece();
}

int Board::clearCompletedLines() noexcept {
    int lines_cleared = 0;
    
    for (int row = BOARD_HEIGHT - 1; row >= 0; row--) {
        if (isLineComplete(row)) {
            removeLine(row);
            lines_cleared++;
            row++; // 같은 행을 다시 검사 (위 행이 내려왔으므로)
        }
    }
    
    if (lines_cleared > 0) {
        lines_cleared_ += lines_cleared;
        
        // 점수 계산
        int points = 0;
        switch (lines_cleared) {
            case 1: points = SCORE_SINGLE * level_; break;
            case 2: points = SCORE_DOUBLE * level_; break;
            case 3: points = SCORE_TRIPLE * level_; break;
            case 4: points = SCORE_TETRIS * level_; break;
        }
        addScore(points);
        
        updateLevel();
    }
    
    return lines_cleared;
}

bool Board::isLineComplete(int row) const noexcept {
    if (row < 0 || row >= BOARD_HEIGHT) return false;
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        if (grid_[row][col] == PieceType::EMPTY) {
            return false;
        }
    }
    return true;
}

void Board::removeLine(int row) noexcept {
    if (row < 0 || row >= BOARD_HEIGHT) return;
    
    // 지정된 행 위의 모든 행을 한 칸씩 아래로 이동
    for (int r = row; r > 0; r--) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            grid_[r][col] = grid_[r - 1][col];
        }
    }
    
    // 맨 위 행을 비움
    for (int col = 0; col < BOARD_WIDTH; col++) {
        grid_[0][col] = PieceType::EMPTY;
    }
}

PieceType Board::getCellType(int x, int y) const noexcept {
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return PieceType::EMPTY;
    }
    return grid_[y][x];
}

void Board::addScore(unsigned long points) noexcept {
    score_ += points;
}

int Board::getDropInterval() const noexcept {
    // 레벨에 따른 낙하 간격 (밀리초)
    int base_interval = 1000; // 1초
    int level_speedup = (level_ - 1) * 50; // 레벨당 50ms씩 빨라짐
    return std::max(100, base_interval - level_speedup); // 최소 100ms
}

Piece Board::calculateGhostPiece() const noexcept {
    if (!current_piece_) {
        return Piece();
    }
    
    Piece ghost = *current_piece_;
    
    // 바닥까지 떨어뜨리기
    while (true) {
        Piece test_piece = ghost;
        test_piece.moveDown();
        
        if (!isValidPosition(test_piece)) {
            break;
        }
        ghost.moveDown();
    }
    
    return ghost;
}

bool Board::isGameOver() const noexcept {
    return state_ == GameState::GAME_OVER;
}

int Board::getBoardHeight() const noexcept {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            if (grid_[row][col] != PieceType::EMPTY) {
                return BOARD_HEIGHT - row;
            }
        }
    }
    return 0;
}

int Board::countHoles() const noexcept {
    int holes = 0;
    
    for (int col = 0; col < BOARD_WIDTH; col++) {
        bool found_block = false;
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            if (grid_[row][col] != PieceType::EMPTY) {
                found_block = true;
            } else if (found_block) {
                holes++;
            }
        }
    }
    
    return holes;
}

void Board::draw(int start_x, int start_y, bool show_ghost) const noexcept {
    // 보드 테두리 그리기
    for (int row = 0; row <= BOARD_HEIGHT; row++) {
        mvaddch(start_y + row, start_x - 1, '|');
        mvaddch(start_y + row, start_x + BOARD_WIDTH * 2, '|');
    }
    
    for (int col = 0; col <= BOARD_WIDTH * 2; col++) {
        mvaddch(start_y + BOARD_HEIGHT, start_x - 1 + col, '-');
    }
    
    // 보드 내용 그리기
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            drawCell(start_x + col * 2, start_y + row, grid_[row][col]);
        }
    }
    
    // 그림자 조각 그리기
    if (show_ghost && current_piece_) {
        Piece ghost = calculateGhostPiece();
        auto positions = ghost.getBlockPositions();
        for (const auto& pos : positions) {
            if (pos.y >= 0 && pos.y < BOARD_HEIGHT && pos.x >= 0 && pos.x < BOARD_WIDTH) {
                if (grid_[pos.y][pos.x] == PieceType::EMPTY) {
                    drawCell(start_x + pos.x * 2, start_y + pos.y, ghost.getType(), true);
                }
            }
        }
    }
    
    // 현재 조각 그리기
    if (current_piece_) {
        auto positions = current_piece_->getBlockPositions();
        for (const auto& pos : positions) {
            if (pos.y >= 0 && pos.y < BOARD_HEIGHT && pos.x >= 0 && pos.x < BOARD_WIDTH) {
                drawCell(start_x + pos.x * 2, start_y + pos.y, current_piece_->getType());
            }
        }
    }
}

void Board::drawNextPiece(int start_x, int start_y) const noexcept {
    mvaddstr(start_y - 1, start_x, "Next:");
    
    // 영역 지우기
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            mvaddstr(start_y + row, start_x + col * 2, "  ");
        }
    }
    
    if (next_piece_) {
        const auto& shape = next_piece_->getShape();
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (shape[row][col]) {
                    drawCell(start_x + col * 2, start_y + row, next_piece_->getType());
                }
            }
        }
    }
}

void Board::drawHoldPiece(int start_x, int start_y) const noexcept {
    mvaddstr(start_y - 1, start_x, "Hold:");
    
    // 영역 지우기
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            mvaddstr(start_y + row, start_x + col * 2, "  ");
        }
    }
    
    if (hold_piece_) {
        const auto& shape = hold_piece_->getShape();
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if (shape[row][col]) {
                    drawCell(start_x + col * 2, start_y + row, hold_piece_->getType());
                }
            }
        }
    }
}

void Board::drawGameInfo(int start_x, int start_y) const noexcept {
    mvprintw(start_y, start_x, "Score: %lu", score_);
    mvprintw(start_y + 1, start_x, "Lines: %d", lines_cleared_);
    mvprintw(start_y + 2, start_x, "Level: %d", level_);
    
    mvprintw(start_y + 4, start_x, "Controls:");
    mvprintw(start_y + 5, start_x, "A/D - Move");
    mvprintw(start_y + 6, start_x, "S - Soft Drop");
    mvprintw(start_y + 7, start_x, "W - Rotate");
    mvprintw(start_y + 8, start_x, "Space - Hard Drop");
    mvprintw(start_y + 9, start_x, "C - Hold");
    mvprintw(start_y + 10, start_x, "P - Pause");
    mvprintw(start_y + 11, start_x, "Q - Quit");
}

void Board::clearGrid() noexcept {
    for (int row = 0; row < BOARD_HEIGHT; row++) {
        for (int col = 0; col < BOARD_WIDTH; col++) {
            grid_[row][col] = PieceType::EMPTY;
        }
    }
}

void Board::updateLevel() noexcept {
    int new_level = (lines_cleared_ / 10) + 1;
    if (new_level > level_) {
        level_ = new_level;
        triggerEvent(GameEvent::LEVEL_UP, level_);
    }
}

void Board::triggerEvent(GameEvent event, int value) noexcept {
    if (event_callback_) {
        event_callback_(event, value);
    }
}

Piece Board::tryWallKick(const Piece& piece, RotationDirection direction) const noexcept {
    // 간단한 Wall Kick 구현
    std::vector<Position> kick_tests = {
        {0, 0},   // 원래 위치
        {-1, 0},  // 왼쪽
        {1, 0},   // 오른쪽
        {0, -1},  // 위
        {-1, -1}, // 왼쪽 위
        {1, -1}   // 오른쪽 위
    };
    
    for (const auto& kick : kick_tests) {
        Piece test_piece = piece;
        test_piece.move(kick);
        
        if (isValidPosition(test_piece)) {
            return test_piece;
        }
    }
    
    // 회전 불가능
    Piece original = piece;
    original.rotate(direction == RotationDirection::CLOCKWISE ? 
                   RotationDirection::COUNTERCLOCKWISE : RotationDirection::CLOCKWISE);
    return original;
}

void Board::drawCell(int x, int y, PieceType type, bool is_ghost) const noexcept {
    if (type == PieceType::EMPTY) {
        mvaddstr(y, x, "  ");
        return;
    }
    
    char block_char = is_ghost ? ':' : '#';
    char display[3] = {block_char, block_char, '\0'};
    
    mvaddstr(y, x, display);
}

} // namespace tetris
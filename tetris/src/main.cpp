#include <ncurses.h>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

class Block {
private:
    std::vector<std::vector<int>> shape;
    int x, y;
    int type;

public:
    Block(int blockType) : type(blockType), x(4), y(0) {
        initShape();
    }

    void initShape() {
        // Initialize with proper bounds - all shapes are 4x4 maximum
        shape = std::vector<std::vector<int>>(4, std::vector<int>(4, 0));
        
        switch(type) {
            case 0: // I-piece
                shape[1][0] = shape[1][1] = shape[1][2] = shape[1][3] = 1;
                break;
            case 1: // O-piece
                shape[0][1] = shape[0][2] = shape[1][1] = shape[1][2] = 1;
                break;
            case 2: // T-piece
                shape[0][1] = shape[1][0] = shape[1][1] = shape[1][2] = 1;
                break;
            case 3: // S-piece
                shape[0][1] = shape[0][2] = shape[1][0] = shape[1][1] = 1;
                break;
            case 4: // Z-piece
                shape[0][0] = shape[0][1] = shape[1][1] = shape[1][2] = 1;
                break;
            case 5: // J-piece
                shape[0][0] = shape[1][0] = shape[1][1] = shape[1][2] = 1;
                break;
            case 6: // L-piece
                shape[0][2] = shape[1][0] = shape[1][1] = shape[1][2] = 1;
                break;
        }
    }

    void rotate() {
        if (type == 1) return; // O-piece doesn't rotate
        
        // Create new 4x4 shape for rotation
        std::vector<std::vector<int>> newShape(4, std::vector<int>(4, 0));
        
        // Perform 90-degree clockwise rotation with proper bounds checking
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i < shape.size() && j < shape[i].size()) {
                    newShape[j][3-i] = shape[i][j];
                }
            }
        }
        
        shape = newShape;
    }

    void moveLeft() { x--; }
    void moveRight() { x++; }
    void moveDown() { y++; }

    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    const std::vector<std::vector<int>>& getShape() const { return shape; }
};

class Tetris {
private:
    static const int BOARD_WIDTH = 10;
    static const int BOARD_HEIGHT = 20;
    std::vector<std::vector<int>> board;
    Block currentBlock;
    std::mt19937 rng;
    std::uniform_int_distribution<int> blockDist;
    int score;

public:
    Tetris() : board(BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 0)),
               currentBlock(0),
               rng(std::chrono::steady_clock::now().time_since_epoch().count()),
               blockDist(0, 6),
               score(0) {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        timeout(0);
        curs_set(0);
        
        spawnNewBlock();
    }

    ~Tetris() {
        endwin();
    }

    void spawnNewBlock() {
        currentBlock = Block(blockDist(rng));
    }

    bool isValidPosition(const Block& block, int offsetX = 0, int offsetY = 0) const {
        int newX = block.getX() + offsetX;
        int newY = block.getY() + offsetY;
        const auto& shape = block.getShape();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i < shape.size() && j < shape[i].size() && shape[i][j]) {
                    int boardX = newX + j;
                    int boardY = newY + i;

                    // Check bounds
                    if (boardX < 0 || boardX >= BOARD_WIDTH || 
                        boardY < 0 || boardY >= BOARD_HEIGHT) {
                        return false;
                    }

                    // Check collision with existing blocks
                    if (board[boardY][boardX]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void placeBlock() {
        const auto& shape = currentBlock.getShape();
        int blockX = currentBlock.getX();
        int blockY = currentBlock.getY();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i < shape.size() && j < shape[i].size() && shape[i][j]) {
                    int boardX = blockX + j;
                    int boardY = blockY + i;
                    
                    // Additional bounds checking for safety
                    if (boardX >= 0 && boardX < BOARD_WIDTH && 
                        boardY >= 0 && boardY < BOARD_HEIGHT) {
                        board[boardY][boardX] = 1;
                    }
                }
            }
        }
    }

    void clearLines() {
        for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
            bool fullLine = true;
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (!board[y][x]) {
                    fullLine = false;
                    break;
                }
            }

            if (fullLine) {
                board.erase(board.begin() + y);
                board.insert(board.begin(), std::vector<int>(BOARD_WIDTH, 0));
                score += 100;
                y++; // Check the same line again
            }
        }
    }

    bool isGameOver() const {
        return !isValidPosition(currentBlock);
    }

    void draw() const {
        clear();

        // Draw border and board
        for (int y = 0; y <= BOARD_HEIGHT + 1; y++) {
            for (int x = 0; x <= BOARD_WIDTH + 1; x++) {
                // Ensure coordinates are within screen bounds
                if (y < LINES && x < COLS) {
                    if (y == 0 || y == BOARD_HEIGHT + 1 || x == 0 || x == BOARD_WIDTH + 1) {
                        mvaddch(y, x, '#');
                    } else {
                        int boardX = x - 1;
                        int boardY = y - 1;
                        
                        // Bounds checking for board access
                        if (boardY >= 0 && boardY < BOARD_HEIGHT && 
                            boardX >= 0 && boardX < BOARD_WIDTH) {
                            if (board[boardY][boardX]) {
                                mvaddch(y, x, '*');
                            } else {
                                mvaddch(y, x, ' ');
                            }
                        }
                    }
                }
            }
        }

        // Draw current block
        const auto& shape = currentBlock.getShape();
        int blockX = currentBlock.getX();
        int blockY = currentBlock.getY();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i < shape.size() && j < shape[i].size() && shape[i][j]) {
                    int screenX = blockX + j + 1;
                    int screenY = blockY + i + 1;
                    
                    // Ensure drawing coordinates are within screen bounds
                    if (screenY >= 1 && screenY <= BOARD_HEIGHT && 
                        screenX >= 1 && screenX <= BOARD_WIDTH &&
                        screenY < LINES && screenX < COLS) {
                        mvaddch(screenY, screenX, '*');
                    }
                }
            }
        }

        // Draw score with bounds checking
        if (BOARD_WIDTH + 5 < COLS && 2 < LINES) {
            mvprintw(2, BOARD_WIDTH + 5, "Score: %d", score);
        }
        
        if (BOARD_WIDTH + 5 < COLS && 4 < LINES) {
            mvprintw(4, BOARD_WIDTH + 5, "Controls:");
            mvprintw(5, BOARD_WIDTH + 5, "A/D - Move");
            mvprintw(6, BOARD_WIDTH + 5, "S - Rotate");
            mvprintw(7, BOARD_WIDTH + 5, "Q - Quit");
        }

        refresh();
    }

    void update() {
        if (isValidPosition(currentBlock, 0, 1)) {
            currentBlock.moveDown();
        } else {
            placeBlock();
            clearLines();
            spawnNewBlock();
            // Game over check after spawning new block
            if (!isValidPosition(currentBlock)) {
                return; // Exit update to trigger game over
            }
        }
    }

    void handleInput() {
        int ch = getch();
        switch (ch) {
            case 'a':
            case 'A':
                if (isValidPosition(currentBlock, -1, 0)) {
                    currentBlock.moveLeft();
                }
                break;
            case 'd':
            case 'D':
                if (isValidPosition(currentBlock, 1, 0)) {
                    currentBlock.moveRight();
                }
                break;
            case 's':
            case 'S': {
                Block rotatedBlock = currentBlock;
                rotatedBlock.rotate();
                if (isValidPosition(rotatedBlock)) {
                    currentBlock = rotatedBlock;
                }
                break;
            }
            case 'q':
            case 'Q':
                endwin();
                exit(0);
                break;
        }
    }

    void run() {
        auto lastUpdate = std::chrono::steady_clock::now();
        const auto updateInterval = std::chrono::milliseconds(500);

        while (!isGameOver()) {
            handleInput();

            auto now = std::chrono::steady_clock::now();
            if (now - lastUpdate >= updateInterval) {
                update();
                lastUpdate = now;
            }

            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        // Game over screen with bounds checking
        clear();
        if (LINES > 10 && COLS > 20) {
            mvprintw(LINES/2, COLS/2 - 10, "Game Over! Score: %d", score);
            mvprintw(LINES/2 + 1, COLS/2 - 10, "Press any key to exit");
        }
        refresh();
        getch();
    }
};

int main() {
    try {
        Tetris game;
        game.run();
    } catch (const std::exception& e) {
        endwin();
        return 1;
    }
    return 0;
}
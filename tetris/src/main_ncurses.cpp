#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

// 게임 설정
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int BLOCK_SIZE = 4;

// 테트리스 블록 타입
enum class BlockType {
    I, O, T, S, Z, J, L, EMPTY
};

// 블록 회전 상태
enum class Rotation {
    R0, R90, R180, R270
};

// 테트리스 블록 정의 (4x4 배열)
const bool BLOCKS[7][4][4][4] = {
    // I 블록
    {
        {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // 0도
        {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}}, // 180도
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}  // 270도
    },
    // O 블록
    {
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // 90도
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // 180도
        {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}  // 270도
    },
    // T 블록
    {
        {{0,0,0,0}, {0,1,0,0}, {1,1,1,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,1,0,0}, {0,1,1,0}, {0,1,0,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,1,0,0}}, // 180도
        {{0,0,0,0}, {0,1,0,0}, {1,1,0,0}, {0,1,0,0}}  // 270도
    },
    // S 블록
    {
        {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,1,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {0,1,1,0}, {1,1,0,0}}, // 180도
        {{0,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,1,0,0}}  // 270도
    },
    // Z 블록
    {
        {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,0,1,0}, {0,1,1,0}, {0,1,0,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {1,1,0,0}, {0,1,1,0}}, // 180도
        {{0,0,0,0}, {0,1,0,0}, {1,1,0,0}, {1,0,0,0}}  // 270도
    },
    // J 블록
    {
        {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,1,1,0}, {0,1,0,0}, {0,1,0,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {0,0,1,0}}, // 180도
        {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0}}  // 270도
    },
    // L 블록
    {
        {{0,0,0,0}, {0,0,1,0}, {1,1,1,0}, {0,0,0,0}}, // 0도
        {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,1,0}}, // 90도
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,0}, {1,0,0,0}}, // 180도
        {{0,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,0,0}}  // 270도
    }
};

// 블록 구조체
struct Block {
    BlockType type;
    Rotation rotation;
    int x, y;
    
    Block() : type(BlockType::EMPTY), rotation(Rotation::R0), x(0), y(0) {}
    Block(BlockType t, int posX, int posY) : type(t), rotation(Rotation::R0), x(posX), y(posY) {}
};

class TetrisGame {
private:
    std::vector<std::vector<BlockType>> board;
    Block currentBlock;
    std::mt19937 rng;
    std::uniform_int_distribution<int> blockDist;
    int score;
    int level;
    int linesCleared;
    bool gameOver;  // 게임 오버 상태를 추적하는 변수 추가

public:
    TetrisGame() : board(BOARD_HEIGHT, std::vector<BlockType>(BOARD_WIDTH, BlockType::EMPTY)),
                   rng(std::chrono::steady_clock::now().time_since_epoch().count()),
                   blockDist(0, 6), score(0), level(1), linesCleared(0), gameOver(false) {
        spawnNewBlock();
    }

    void spawnNewBlock() {
        BlockType newType = static_cast<BlockType>(blockDist(rng));
        currentBlock = Block(newType, BOARD_WIDTH / 2 - 2, 0);
        
        // 새 블록이 유효한 위치에 놓일 수 있는지 확인
        if (!isValidPosition(currentBlock)) {
            gameOver = true;  // 게임 오버 상태 설정
        }
    }

    bool isValidPosition(const Block& block) const {
        if (block.type == BlockType::EMPTY) return false;
        
        int typeIndex = static_cast<int>(block.type);
        int rotIndex = static_cast<int>(block.rotation);
        
        for (int y = 0; y < BLOCK_SIZE; y++) {
            for (int x = 0; x < BLOCK_SIZE; x++) {
                if (BLOCKS[typeIndex][rotIndex][y][x]) {
                    int boardX = block.x + x;
                    int boardY = block.y + y;
                    
                    // 경계 체크
                    if (boardX < 0 || boardX >= BOARD_WIDTH || 
                        boardY < 0 || boardY >= BOARD_HEIGHT) {
                        return false;
                    }
                    
                    // 다른 블록과의 충돌 체크
                    if (board[boardY][boardX] != BlockType::EMPTY) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void placeBlock() {
        if (currentBlock.type == BlockType::EMPTY) return;
        
        int typeIndex = static_cast<int>(currentBlock.type);
        int rotIndex = static_cast<int>(currentBlock.rotation);
        
        for (int y = 0; y < BLOCK_SIZE; y++) {
            for (int x = 0; x < BLOCK_SIZE; x++) {
                if (BLOCKS[typeIndex][rotIndex][y][x]) {
                    int boardX = currentBlock.x + x;
                    int boardY = currentBlock.y + y;
                    if (boardX >= 0 && boardX < BOARD_WIDTH && 
                        boardY >= 0 && boardY < BOARD_HEIGHT) {
                        board[boardY][boardX] = currentBlock.type;
                    }
                }
            }
        }
    }

    void clearLines() {
        int linesCleared = 0;
        for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
            bool fullLine = true;
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (board[y][x] == BlockType::EMPTY) {
                    fullLine = false;
                    break;
                }
            }
            
            if (fullLine) {
                board.erase(board.begin() + y);
                board.insert(board.begin(), std::vector<BlockType>(BOARD_WIDTH, BlockType::EMPTY));
                linesCleared++;
                y++; // 같은 라인을 다시 체크하기 위해
            }
        }
        
        if (linesCleared > 0) {
            this->linesCleared += linesCleared;
            score += linesCleared * 100 * level;
            level = (this->linesCleared / 10) + 1;
        }
    }

    bool moveBlock(int dx, int dy) {
        Block newBlock = currentBlock;
        newBlock.x += dx;
        newBlock.y += dy;
        
        if (isValidPosition(newBlock)) {
            currentBlock = newBlock;
            return true;
        }
        return false;
    }

    bool rotateBlock() {
        Block newBlock = currentBlock;
        newBlock.rotation = static_cast<Rotation>((static_cast<int>(newBlock.rotation) + 1) % 4);
        
        if (isValidPosition(newBlock)) {
            currentBlock = newBlock;
            return true;
        }
        return false;
    }

    void update() {
        if (gameOver) return;  // 게임이 이미 끝났다면 업데이트하지 않음
        
        if (!moveBlock(0, 1)) {
            placeBlock();
            clearLines();
            spawnNewBlock();  // 새 블록 생성 (내부에서 gameOver 상태 확인)
        }
    }

    bool isGameOver() const {
        return gameOver;  // 게임 오버 상태 반환
    }

    void draw() const {
        // 화면 지우기
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
        
        // 현재 블록을 임시로 보드에 그리기 위한 복사본 생성
        auto displayBoard = board;
        
        // 현재 블록을 임시 보드에 그리기
        if (currentBlock.type != BlockType::EMPTY && !gameOver) {
            int typeIndex = static_cast<int>(currentBlock.type);
            int rotIndex = static_cast<int>(currentBlock.rotation);
            
            for (int y = 0; y < BLOCK_SIZE; y++) {
                for (int x = 0; x < BLOCK_SIZE; x++) {
                    if (BLOCKS[typeIndex][rotIndex][y][x]) {
                        int boardX = currentBlock.x + x;
                        int boardY = currentBlock.y + y;
                        if (boardX >= 0 && boardX < BOARD_WIDTH && 
                            boardY >= 0 && boardY < BOARD_HEIGHT) {
                            displayBoard[boardY][boardX] = currentBlock.type;
                        }
                    }
                }
            }
        }
        
        // 상단 경계
        std::cout << "+";
        for (int x = 0; x < BOARD_WIDTH; x++) {
            std::cout << "-";
        }
        std::cout << "+\n";
        
        // 게임 보드 그리기
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            std::cout << "|";
            for (int x = 0; x < BOARD_WIDTH; x++) {
                char ch = ' ';
                switch (displayBoard[y][x]) {
                    case BlockType::I: ch = 'I'; break;
                    case BlockType::O: ch = 'O'; break;
                    case BlockType::T: ch = 'T'; break;
                    case BlockType::S: ch = 'S'; break;
                    case BlockType::Z: ch = 'Z'; break;
                    case BlockType::J: ch = 'J'; break;
                    case BlockType::L: ch = 'L'; break;
                    case BlockType::EMPTY: ch = ' '; break;
                }
                std::cout << ch;
            }
            std::cout << "|\n";
        }
        
        // 하단 경계
        std::cout << "+";
        for (int x = 0; x < BOARD_WIDTH; x++) {
            std::cout << "-";
        }
        std::cout << "+\n";
        
        // 게임 정보 출력
        std::cout << "Score: " << score << "\n";
        std::cout << "Level: " << level << "\n";
        std::cout << "Lines: " << linesCleared << "\n";
        
        if (gameOver) {
            std::cout << "\n*** GAME OVER ***\n";
            std::cout << "Press 'q' to quit\n";
        } else {
            std::cout << "\nControls: A/D - Move, S - Down, W - Rotate, Q - Quit\n";
        }
    }

    void handleInput() {
        if (gameOver) return;  // 게임이 끝났다면 입력 처리하지 않음
        
        #ifdef _WIN32
        if (_kbhit()) {
            char key = _getch();
            key = tolower(key);
            
            switch (key) {
                case 'a':
                    moveBlock(-1, 0);
                    break;
                case 'd':
                    moveBlock(1, 0);
                    break;
                case 's':
                    moveBlock(0, 1);
                    break;
                case 'w':
                    rotateBlock();
                    break;
                case 'q':
                    gameOver = true;
                    break;
            }
        }
        #else
        // 비동기 입력 체크
        int ch = getchar_async();
        if (ch != -1) {
            char key = tolower(ch);
            
            switch (key) {
                case 'a':
                    moveBlock(-1, 0);
                    break;
                case 'd':
                    moveBlock(1, 0);
                    break;
                case 's':
                    moveBlock(0, 1);
                    break;
                case 'w':
                    rotateBlock();
                    break;
                case 'q':
                    gameOver = true;
                    break;
            }
        }
        #endif
    }

private:
    #ifndef _WIN32
    int getchar_async() {
        int ch = -1;
        struct termios oldt, newt;
        
        // 현재 터미널 설정 저장
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        
        // 비정규 모드로 설정 (엔터 없이 입력 받기)
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        // 비블로킹 모드로 설정
        int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
        
        ch = getchar();
        
        // 원래 설정 복원
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, flags);
        
        return ch;
    }
    #endif
};

int main() {
    TetrisGame game;
    
    auto lastUpdate = std::chrono::steady_clock::now();
    auto updateInterval = std::chrono::milliseconds(1000); // 1초마다 블록 이동
    
    while (!game.isGameOver()) {
        game.handleInput();

        auto now = std::chrono::steady_clock::now();
        if (now - lastUpdate >= updateInterval) {
            game.update();
            lastUpdate = now;
        }

        game.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    // 게임 오버 후 마지막 화면 표시 및 종료 대기
    game.draw();
    
    #ifdef _WIN32
    std::cout << "Press any key to exit...";
    _getch();
    #else
    std::cout << "Press Enter to exit...";
    std::cin.get();
    #endif
    
    return 0;
}
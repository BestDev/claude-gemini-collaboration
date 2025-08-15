#include "board.h"
#include "piece.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

using namespace tetris;

class SimpleConsoleRenderer {
public:
    static void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
    
    static void drawBoard(const Board& board) {
        clearScreen();
        
        std::cout << "=== C++ TETRIS (Console Version) ===\n\n";
        
        // 상단 테두리
        std::cout << "+";
        for (int i = 0; i < Board::BOARD_WIDTH; i++) {
            std::cout << "--";
        }
        std::cout << "+\n";
        
        // 보드 내용
        for (int row = 0; row < Board::BOARD_HEIGHT; row++) {
            std::cout << "|";
            for (int col = 0; col < Board::BOARD_WIDTH; col++) {
                PieceType cell = board.getCellType(col, row);
                if (cell == PieceType::EMPTY) {
                    std::cout << "  ";
                } else {
                    std::cout << "##";
                }
            }
            std::cout << "|\n";
        }
        
        // 하단 테두리
        std::cout << "+";
        for (int i = 0; i < Board::BOARD_WIDTH; i++) {
            std::cout << "--";
        }
        std::cout << "+\n\n";
        
        // 게임 정보
        std::cout << "Score: " << board.getScore() << "\n";
        std::cout << "Lines: " << board.getLinesCleared() << "\n";
        std::cout << "Level: " << board.getLevel() << "\n\n";
        
        // 컨트롤 안내
        std::cout << "Controls:\n";
        std::cout << "A/D - Move Left/Right\n";
        std::cout << "S - Soft Drop\n";
        std::cout << "W - Rotate\n";
        std::cout << "Q - Quit\n\n";
        
        // 게임 상태
        switch (board.getState()) {
            case GameState::PAUSED:
                std::cout << "*** PAUSED ***\n";
                std::cout << "Press P to resume\n";
                break;
            case GameState::GAME_OVER:
                std::cout << "*** GAME OVER ***\n";
                std::cout << "Final Score: " << board.getScore() << "\n";
                std::cout << "Press Q to quit\n";
                break;
            default:
                break;
        }
    }
    
    static bool kbhit() {
#ifdef _WIN32
        return _kbhit();
#else
        struct termios oldt, newt;
        int ch;
        int oldf;
        
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        
        ch = getchar();
        
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        
        if (ch != EOF) {
            ungetc(ch, stdin);
            return true;
        }
        
        return false;
#endif
    }
    
    static char getch() {
#ifdef _WIN32
        return _getch();
#else
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }
};

class SimpleTetrisGame {
private:
    Board board_;
    bool is_running_;
    std::chrono::steady_clock::time_point last_drop_time_;
    
public:
    SimpleTetrisGame() : is_running_(true) {
        last_drop_time_ = std::chrono::steady_clock::now();
        board_.initialize();
    }
    
    void processInput() {
        if (!SimpleConsoleRenderer::kbhit()) {
            return;
        }
        
        char ch = SimpleConsoleRenderer::getch();
        
        switch (ch) {
            case 'q':
            case 'Q':
                is_running_ = false;
                break;
                
            case 'p':
            case 'P':
                if (board_.getState() == GameState::PLAYING) {
                    board_.setState(GameState::PAUSED);
                } else if (board_.getState() == GameState::PAUSED) {
                    board_.setState(GameState::PLAYING);
                }
                break;
                
            case 'a':
            case 'A':
                if (board_.getState() == GameState::PLAYING) {
                    board_.moveCurrentPieceLeft();
                }
                break;
                
            case 'd':
            case 'D':
                if (board_.getState() == GameState::PLAYING) {
                    board_.moveCurrentPieceRight();
                }
                break;
                
            case 's':
            case 'S':
                if (board_.getState() == GameState::PLAYING) {
                    board_.moveCurrentPieceDown();
                }
                break;
                
            case 'w':
            case 'W':
                if (board_.getState() == GameState::PLAYING) {
                    board_.rotateCurrentPiece();
                }
                break;
        }
    }
    
    void update() {
        if (board_.getState() != GameState::PLAYING) {
            return;
        }
        
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - last_drop_time_).count();
        
        // 자동 낙하
        if (elapsed >= board_.getDropInterval()) {
            if (!board_.moveCurrentPieceDown()) {
                board_.lockCurrentPiece();
            }
            last_drop_time_ = now;
        }
        
        // 게임 오버 체크
        if (board_.isGameOver()) {
            board_.setState(GameState::GAME_OVER);
        }
    }
    
    void render() {
        SimpleConsoleRenderer::drawBoard(board_);
    }
    
    void run() {
        std::cout << "C++ Tetris Console Version\n";
        std::cout << "Press any key to start...\n";
        SimpleConsoleRenderer::getch();
        
        while (is_running_) {
            processInput();
            update();
            render();
            
            // CPU 사용량 제한
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        std::cout << "\nThank you for playing C++ Tetris!\n";
        std::cout << "Final Score: " << board_.getScore() << std::endl;
    }
};

int main() {
    try {
        SimpleTetrisGame game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    
    return 0;
}
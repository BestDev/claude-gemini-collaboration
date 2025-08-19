#include "Renderer.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

namespace Tetris {

// Platform-specific data structures
struct ConsoleRenderer::PlatformData {
#ifdef _WIN32
    HANDLE hConsole;
    CONSOLE_SCREEN_BUFFER_INFO original_csbi;
    WORD original_attributes;
#else
    // Linux/macOS specific data can be added here if needed
#endif
};

// --- Constructor / Destructor ---

ConsoleRenderer::ConsoleRenderer(const RenderConfig& config)
    : config_(config), initialized_(false), platform_data_(std::make_unique<PlatformData>()) {}

ConsoleRenderer::ConsoleRenderer() : ConsoleRenderer(RenderConfig{}) {}

ConsoleRenderer::~ConsoleRenderer() {
    if (initialized_) {
        shutdown();
    }
}

// --- Public API ---

bool ConsoleRenderer::initialize() {
    if (initialized_) return true;
    initialized_ = platformInitialize();
    if (initialized_) {
        console_size_ = getConsoleDimensions();
        board_cache_.resize(Board::HEIGHT, std::string(Board::WIDTH * (config_.double_width ? 2 : 1), ' '));
        clearScreen();
        setCursorVisible(false);
    }
    return initialized_;
}

void ConsoleRenderer::shutdown() {
    if (!initialized_) return;
    setCursorVisible(true);
    resetColors();
    platformShutdown();
    initialized_ = false;
}

void ConsoleRenderer::clearScreen() {
    platformClearScreen();
    setCursorPosition(0, 0);
}

void ConsoleRenderer::refresh() {
    cache_dirty_ = true;
    // A full render will be triggered on the next call to render()
}

void ConsoleRenderer::render(const Board& board, const Tetromino& current_piece, const GameStats& stats) {
    if (!initialized_) return;

    Board render_board = board;
    if (config_.show_ghost_piece && current_piece.isValid()) {
        render_board = board.getPreviewBoard(current_piece);
    }

    renderBoard(render_board, current_piece);
    renderStats(stats);
    
    // Flush output buffer
    std::cout << std::flush;
}

void ConsoleRenderer::renderBoard(const Board& board, const Tetromino& current_piece) {
    if (!initialized_) return;

    const auto board_pos = getBoardRenderPosition();
    renderBoardFrame();

    // Draw the board state
    const auto& grid = board.getGrid();
    for (int y = 0; y < Board::HEIGHT; ++y) {
        for (int x = 0; x < Board::WIDTH; ++x) {
            renderCell(grid[y][x], board_pos.x + x * (config_.double_width ? 2 : 1), board_pos.y + y);
        }
    }

    // Draw the current piece
    if (current_piece.isValid()) {
        const auto& piece_pos = current_piece.getPosition();
        const auto& shape = current_piece.getCurrentShape();
        const Color piece_color = getPieceColor(current_piece.getType());

        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (shape[y][x]) {
                    int board_x = piece_pos.x + x;
                    int board_y = piece_pos.y + y;
                    if (board_x >= 0 && board_x < Board::WIDTH && board_y >= 0 && board_y < Board::HEIGHT) {
                        setCursorPosition(board_pos.x + board_x * (config_.double_width ? 2 : 1), board_pos.y + board_y);
                        setTextColor(piece_color);
                        printText(config_.double_width ? "[]" : "#");
                    }
                }
            }
        }
    }
    resetColors();
}

void ConsoleRenderer::renderStats(const GameStats& stats) {
    if (!initialized_) return;
    const auto stats_pos = getStatsPanelPosition();
    
    resetColors();
    printTextAt(stats_pos.x, stats_pos.y,     "T E T R I S");
    printTextAt(stats_pos.x, stats_pos.y + 2, "-----------");
    printTextAt(stats_pos.x, stats_pos.y + 3, "Score: " + std::to_string(stats.score));
    printTextAt(stats_pos.x, stats_pos.y + 4, "Level: " + std::to_string(stats.level));
    printTextAt(stats_pos.x, stats_pos.y + 5, "Lines: " + std::to_string(stats.lines_cleared));
    
    renderNextPiece(createTetromino(stats.next_piece));
    renderHeldPiece(createTetromino(stats.held_piece), stats.can_hold);
}

void ConsoleRenderer::renderNextPiece(const Tetromino& next_piece) {
    renderPiecePreview(next_piece, getStatsPanelPosition().x, getStatsPanelPosition().y + 7, "Next:");
}

void ConsoleRenderer::renderHeldPiece(const Tetromino& held_piece, bool can_hold) {
    if (!can_hold && !held_piece.isValid()) {
        return; // Don't render if nothing is held and cannot hold
    }
    renderPiecePreview(held_piece, getStatsPanelPosition().x, getStatsPanelPosition().y + 13, "Hold:");
    if (!can_hold) {
        setTextColor(Color::GRAY);
        printTextAt(getStatsPanelPosition().x, getStatsPanelPosition().y + 13, "Hold: (X)");
        resetColors();
    }
}

void ConsoleRenderer::renderGameOver(int final_score, int final_level) {
    if (!initialized_) return;
    const auto center_x = console_size_.x / 2;
    const auto center_y = console_size_.y / 2;

    std::string box_top = "+------------------------+";
    std::string box_mid = "|                        |";
    std::string box_bot = "+------------------------+";

    printTextAt(center_x - box_top.length() / 2, center_y - 4, box_top);
    printTextAt(center_x - box_top.length() / 2, center_y - 3, box_mid);
    printTextAt(center_x - box_top.length() / 2, center_y - 2, box_mid);
    printTextAt(center_x - box_top.length() / 2, center_y - 1, box_mid);
    printTextAt(center_x - box_top.length() / 2, center_y,     box_mid);
    printTextAt(center_x - box_top.length() / 2, center_y + 1, box_bot);

    setTextColor(Color::BRIGHT_RED);
    printTextAt(center_x - 5, center_y - 3, "GAME OVER");
    resetColors();
    
    printTextAt(center_x - 10, center_y - 1, "Final Score: " + std::to_string(final_score));
    printTextAt(center_x - 10, center_y,     "Final Level: " + std::to_string(final_level));
    
    printTextAt(center_x - 12, center_y + 3, "Press R to Restart");
    printTextAt(center_x - 12, center_y + 4, "Press Q to Quit");
    std::cout << std::flush;
}

void ConsoleRenderer::renderPause() {
    if (!initialized_) return;
    const auto center_x = console_size_.x / 2;
    const auto center_y = console_size_.y / 2;
    
    std::string text = "|| PAUSED ||";
    setTextColor(Color::BRIGHT_YELLOW);
    printTextAt(center_x - text.length() / 2, center_y, text);
    resetColors();
    std::cout << std::flush;
}

void ConsoleRenderer::renderMenu(int selected_option) {
    clearScreen();
    const auto center_x = console_size_.x / 2;
    const auto center_y = console_size_.y / 2;
    
    printTextAt(center_x - 5, center_y - 4, "T E T R I S");
    
    std::vector<std::string> options = {"New Game", "Help", "Quit"};
    for (size_t i = 0; i < options.size(); ++i) {
        if (static_cast<int>(i) == selected_option) {
            setTextColor(Color::BRIGHT_YELLOW);
            printTextAt(center_x - 7, center_y - 1 + static_cast<int>(i), ">> " + options[i] + " <<");
        } else {
            resetColors();
            printTextAt(center_x - 7, center_y - 1 + static_cast<int>(i), "   " + options[i] + "   ");
        }
    }
    resetColors();
    std::cout << std::flush;
}

void ConsoleRenderer::renderHelp() {
    clearScreen();
    const auto center_x = console_size_.x / 2;
    const auto center_y = console_size_.y / 2;
    
    printTextAt(center_x - 4, center_y - 6, "CONTROLS");
    printTextAt(center_x - 10, center_y - 4, "Left/Right : Move");
    printTextAt(center_x - 10, center_y - 3, "Up/Z       : Rotate CW");
    printTextAt(center_x - 10, center_y - 2, "X          : Rotate CCW");
    printTextAt(center_x - 10, center_y - 1, "Down       : Soft Drop");
    printTextAt(center_x - 10, center_y - 0, "Space      : Hard Drop");
    printTextAt(center_x - 10, center_y + 1, "C          : Hold");
    printTextAt(center_x - 10, center_y + 2, "P          : Pause");
    printTextAt(center_x - 10, center_y + 3, "Q          : Quit");
    
    printTextAt(center_x - 10, center_y + 6, "Press any key to return...");
    std::cout << std::flush;
}

// --- Platform-specific Implementations ---

#ifdef _WIN32
bool ConsoleRenderer::platformInitialize() {
    platform_data_->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (platform_data_->hConsole == INVALID_HANDLE_VALUE) {
        return false;
    }
    if (!GetConsoleScreenBufferInfo(platform_data_->hConsole, &platform_data_->original_csbi)) {
        return false;
    }
    platform_data_->original_attributes = platform_data_->original_csbi.wAttributes;
    return true;
}

void ConsoleRenderer::platformShutdown() {
    SetConsoleTextAttribute(platform_data_->hConsole, platform_data_->original_attributes);
}

void ConsoleRenderer::platformClearScreen() {
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(platform_data_->hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(platform_data_->hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(platform_data_->hConsole, &csbi);
    FillConsoleOutputAttribute(platform_data_->hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
}

void ConsoleRenderer::platformSetCursorPosition(int x, int y) {
    SetConsoleCursorPosition(platform_data_->hConsole, {(SHORT)x, (SHORT)y});
}

void ConsoleRenderer::platformSetCursorVisible(bool visible) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(platform_data_->hConsole, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(platform_data_->hConsole, &cursorInfo);
}

Position ConsoleRenderer::platformGetConsoleSize() const {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(platform_data_->hConsole, &csbi)) {
        return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
    }
    return {80, 24}; // Default
}

void ConsoleRenderer::platformSetColors(Color text_color, Color bg_color) {
    int text = static_cast<int>(text_color);
    int bg = static_cast<int>(bg_color);
    SetConsoleTextAttribute(platform_data_->hConsole, text | (bg << 4));
}

#else // Linux/macOS
bool ConsoleRenderer::platformInitialize() {
    // Set terminal to raw mode, etc. is handled by InputHandler
    return true;
}

void ConsoleRenderer::platformShutdown() {
    resetColors();
    // Restore terminal state is handled by InputHandler
}

void ConsoleRenderer::platformClearScreen() {
    std::cout << "[2J";
}

void ConsoleRenderer::platformSetCursorPosition(int x, int y) {
    std::cout << "[" << y + 1 << ";" << x + 1 << "H";
}

void ConsoleRenderer::platformSetCursorVisible(bool visible) {
    std::cout << (visible ? "[?25h" : "[?25l");
}

Position ConsoleRenderer::platformGetConsoleSize() const {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
}

void ConsoleRenderer::platformSetColors(Color text_color, Color bg_color) {
    int text = static_cast<int>(text_color);
    int bg = static_cast<int>(bg_color);
    
    if (text < 8) std::cout << "[" << 30 + text << "m";
    else std::cout << "[" << 90 + (text - 8) << "m";
    
    if (bg < 8) std::cout << "[" << 40 + bg << "m";
    else std::cout << "[" << 100 + (bg - 8) << "m";
}
#endif

// --- Private Helper Methods ---

void ConsoleRenderer::setCursorPosition(int x, int y) {
    platformSetCursorPosition(x, y);
}

void ConsoleRenderer::setCursorVisible(bool visible) {
    platformSetCursorVisible(visible);
}

Position ConsoleRenderer::getConsoleDimensions() const {
    return platformGetConsoleSize();
}

void ConsoleRenderer::setTextColor(Color color) {
    platformSetColors(color, Color::BLACK);
}

void ConsoleRenderer::setBackgroundColor(Color /*color*/) {
    // Not directly used, but here for completeness
}

void ConsoleRenderer::resetColors() {
#ifdef _WIN32
    SetConsoleTextAttribute(platform_data_->hConsole, platform_data_->original_attributes);
#else
    std::cout << "[0m";
#endif
}

void ConsoleRenderer::printText(const std::string& text) {
    std::cout << text;
}

void ConsoleRenderer::printTextAt(int x, int y, const std::string& text) {
    setCursorPosition(x, y);
    printText(text);
}

void ConsoleRenderer::renderCell(const Cell& cell, int x, int y, bool /*show_ghost*/) {
    setCursorPosition(x, y);
    if (cell.occupied) {
        setTextColor(getPieceColor(static_cast<TetrominoType>(cell.color - 1)));
        printText(config_.double_width ? "[]" : "#");
    } else if (cell.color != 0) { // Ghost piece
        setTextColor(Color::GRAY);
        printText(config_.double_width ? "<>" : "x");
    }
    else {
        printText(config_.double_width ? "  " : " ");
    }
}

void ConsoleRenderer::renderBoardFrame() {
    const auto pos = getBoardRenderPosition();
    const int width = Board::WIDTH * (config_.double_width ? 2 : 1);
    const int height = Board::HEIGHT;

    resetColors();
    for (int y = 0; y < height; ++y) {
        printTextAt(pos.x - 1, pos.y + y, "|");
        printTextAt(pos.x + width, pos.y + y, "|");
    }
    std::string border(width, '-');
    printTextAt(pos.x, pos.y - 1, border);
    printTextAt(pos.x, pos.y + height, border);
}

void ConsoleRenderer::renderPiecePreview(const Tetromino& piece, int start_x, int start_y, const std::string& title) {
    resetColors();
    printTextAt(start_x, start_y, title);
    
    // Clear area
    for (int y = 0; y < 4; ++y) {
        printTextAt(start_x, start_y + 1 + y, "        ");
    }

    if (piece.isValid()) {
        const auto& shape = piece.getCurrentShape();
        const Color color = getPieceColor(piece.getType());
        setTextColor(color);
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (shape[y][x]) {
                    printTextAt(start_x + x * 2, start_y + 1 + y, "[]");
                }
            }
        }
    }
    resetColors();
}

Color ConsoleRenderer::getPieceColor(TetrominoType piece_type) const noexcept {
    switch (piece_type) {
        case TetrominoType::I: return Color::CYAN;
        case TetrominoType::O: return Color::YELLOW;
        case TetrominoType::T: return Color::MAGENTA;
        case TetrominoType::S: return Color::GREEN;
        case TetrominoType::Z: return Color::RED;
        case TetrominoType::J: return Color::BLUE;
        case TetrominoType::L: return Color::BRIGHT_YELLOW; // Orange
        default: return Color::GRAY;
    }
}

Position ConsoleRenderer::getBoardRenderPosition() const {
    return { (console_size_.x / 2) - (Board::WIDTH * (config_.double_width ? 2 : 1) / 2), 2 };
}

Position ConsoleRenderer::getStatsPanelPosition() const {
    return { getBoardRenderPosition().x + (Board::WIDTH * (config_.double_width ? 2 : 1)) + 3, 2 };
}


// --- RAII Wrapper ---

RenderSystem::RenderSystem() : renderer_() {
    renderer_.initialize();
}

RenderSystem::RenderSystem(const RenderConfig& config) : renderer_(config) {
    renderer_.initialize();
}

RenderSystem::~RenderSystem() {
    renderer_.shutdown();
}

} // namespace Tetris

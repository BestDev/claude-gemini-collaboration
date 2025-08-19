#include "Input.h"
#include <stdexcept>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#endif

namespace Tetris {

// --- Platform-specific data and implementation ---

struct InputHandler::PlatformData {
#ifdef _WIN32
    // No specific data needed for Windows conio.h implementation
#else
    struct termios original_termios;
#endif
};

#ifdef _WIN32
// Windows Implementation
bool InputHandler::platformInitialize() {
    // No initialization needed for conio.h
    return true;
}

void InputHandler::platformShutdown() {
    // No shutdown needed for conio.h
}

bool InputHandler::platformHasInput() const {
    return _kbhit();
}

InputAction InputHandler::platformPollInput() {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 0 || ch == 224) { // Arrow keys
            ch = _getch();
            switch (ch) {
                case 72: return InputAction::ROTATE_CW; // Up
                case 80: return InputAction::SOFT_DROP; // Down
                case 75: return InputAction::MOVE_LEFT; // Left
                case 77: return InputAction::MOVE_RIGHT; // Right
                default: return InputAction::NONE;
            }
        }
        return keyCodeToAction(ch);
    }
    return InputAction::NONE;
}

#else
// Linux/macOS Implementation
bool InputHandler::platformInitialize() {
    if (tcgetattr(STDIN_FILENO, &platform_data_->original_termios) == -1) {
        return false;
    }
    struct termios raw = platform_data_->original_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        return false;
    }
    return true;
}

void InputHandler::platformShutdown() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &platform_data_->original_termios);
}

bool InputHandler::platformHasInput() const {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

InputAction InputHandler::platformPollInput() {
    char c = '\0';
    if (read(STDIN_FILENO, &c, 1) > 0) {
        if (c == '\033') { // Escape sequence
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 0) return InputAction::NONE;
            if (read(STDIN_FILENO, &seq[1], 1) == 0) return InputAction::NONE;
            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'A': return InputAction::ROTATE_CW; // Up
                    case 'B': return InputAction::SOFT_DROP; // Down
                    case 'C': return InputAction::MOVE_RIGHT; // Right
                    case 'D': return InputAction::MOVE_LEFT; // Left
                }
            }
        }
        return keyCodeToAction(c);
    }
    return InputAction::NONE;
}
#endif

// --- Constructor / Destructor ---

InputHandler::InputHandler(const Config& config)
    : config_(config), initialized_(false), platform_data_(std::make_unique<PlatformData>()) {}

InputHandler::InputHandler() : InputHandler(Config{}) {}

InputHandler::~InputHandler() {
    if (initialized_) {
        shutdown();
    }
}

// --- Public API ---

bool InputHandler::initialize() {
    if (initialized_) return true;
    initialized_ = platformInitialize();
    return initialized_;
}

void InputHandler::shutdown() {
    if (!initialized_) return;
    platformShutdown();
    initialized_ = false;
}

InputState InputHandler::pollInput() {
    if (!initialized_) return {};
    
    InputAction action = platformPollInput();
    if (action != InputAction::NONE) {
        return {action, true};
    }
    return {};
}

void InputHandler::clearInput() {
    while(hasInput()) {
        [[maybe_unused]] auto action = platformPollInput();
    }
}

bool InputHandler::hasInput() const {
    if (!initialized_) return false;
    return platformHasInput();
}

InputState InputHandler::waitForInput() {
    if (!initialized_) return {};
    while (!hasInput()) {
        // Wait
#ifdef _WIN32
        Sleep(10); // Prevent busy-waiting
#else
        usleep(10000); // 10ms
#endif
    }
    return pollInput();
}

InputAction InputHandler::keyCodeToAction(int key_code) const noexcept {
    switch (key_code) {
        case 'q': case 'Q': return InputAction::QUIT;
        case 'p': case 'P': return InputAction::PAUSE;
        case 'r': case 'R': return InputAction::RESTART;
        case 'c': case 'C': return InputAction::HOLD;
        case 'z': case 'Z': return InputAction::ROTATE_CW;
        case 'x': case 'X': return InputAction::ROTATE_CCW;
        case ' ': return InputAction::HARD_DROP;
        // Arrow keys are handled in platformPollInput
        default: return InputAction::NONE;
    }
}

const char* InputHandler::actionToString(InputAction action) noexcept {
    switch (action) {
        case InputAction::NONE: return "NONE";
        case InputAction::MOVE_LEFT: return "MOVE_LEFT";
        case InputAction::MOVE_RIGHT: return "MOVE_RIGHT";
        case InputAction::MOVE_DOWN: return "MOVE_DOWN";
        case InputAction::ROTATE_CW: return "ROTATE_CW";
        case InputAction::ROTATE_CCW: return "ROTATE_CCW";
        case InputAction::HARD_DROP: return "HARD_DROP";
        case InputAction::SOFT_DROP: return "SOFT_DROP";
        case InputAction::HOLD: return "HOLD";
        case InputAction::PAUSE: return "PAUSE";
        case InputAction::QUIT: return "QUIT";
        case InputAction::RESTART: return "RESTART";
        default: return "UNKNOWN";
    }
}

// --- RAII Wrapper ---

InputSystem::InputSystem() : handler_() {
    handler_.initialize();
}

InputSystem::InputSystem(const InputHandler::Config& config) : handler_(config) {
    handler_.initialize();
}

InputSystem::~InputSystem() {
    handler_.shutdown();
}

} // namespace Tetris

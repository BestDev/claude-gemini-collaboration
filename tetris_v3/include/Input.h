#pragma once

#include <cstdint>
#include <chrono>
#include <memory>

namespace Tetris {

/**
 * @brief Enumeration of game input actions
 */
enum class InputAction : uint8_t {
    NONE = 0,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN,
    ROTATE_CW,      // Clockwise rotation
    ROTATE_CCW,     // Counter-clockwise rotation
    HARD_DROP,
    SOFT_DROP,
    HOLD,
    PAUSE,
    QUIT,
    RESTART
};

/**
 * @brief Input state structure
 */
struct InputState {
    InputAction action{InputAction::NONE};
    bool pressed{false};
    bool repeat{false};
    std::chrono::steady_clock::time_point timestamp;
    
    InputState() : timestamp(std::chrono::steady_clock::now()) {}
    InputState(InputAction act, bool press, bool rep = false) 
        : action(act), pressed(press), repeat(rep), timestamp(std::chrono::steady_clock::now()) {}
    
    bool isValid() const noexcept { return action != InputAction::NONE; }
    void clear() noexcept { action = InputAction::NONE; pressed = false; repeat = false; }
};

/**
 * @brief Cross-platform input handler for Tetris game
 * 
 * This class provides non-blocking keyboard input handling for both
 * Windows and Linux platforms. It supports key repeat for movement
 * actions and handles the standard Tetris control scheme.
 */
class InputHandler {
public:
    /**
     * @brief Input configuration settings
     */
    struct Config {
        std::chrono::milliseconds repeat_delay{150};        // Initial key repeat delay
        std::chrono::milliseconds repeat_interval{50};      // Key repeat interval
        std::chrono::milliseconds soft_drop_interval{50};   // Soft drop repeat rate
        bool enable_key_repeat{true};                       // Enable key repeat for movement
        
        Config() = default;
    };
    
    /**
     * @brief Construct input handler with default configuration
     */
    InputHandler();
    
    /**
     * @brief Construct input handler with custom configuration
     * @param config Input configuration settings
     */
    explicit InputHandler(const Config& config);
    
    /**
     * @brief Destructor - cleanup platform-specific resources
     */
    ~InputHandler();
    
    // Non-copyable but movable
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
    InputHandler(InputHandler&&) = default;
    InputHandler& operator=(InputHandler&&) = default;
    
    /**
     * @brief Initialize the input system
     * @return True if initialization successful
     */
    bool initialize();
    
    /**
     * @brief Shutdown the input system and restore terminal state
     */
    void shutdown();
    
    /**
     * @brief Poll for input events (non-blocking)
     * @return InputState containing the current input action
     */
    [[nodiscard]] InputState pollInput();
    
    /**
     * @brief Check if a specific action is currently being held
     * @param action The action to check
     * @return True if action key is currently pressed
     */
    [[nodiscard]] bool isActionHeld(InputAction action) const;
    
    /**
     * @brief Update input configuration
     * @param config New configuration settings
     */
    void setConfig(const Config& config) noexcept { config_ = config; }
    
    /**
     * @brief Get current input configuration
     * @return Current configuration settings
     */
    [[nodiscard]] const Config& getConfig() const noexcept { return config_; }
    
    /**
     * @brief Check if input system is initialized
     * @return True if system is ready for input
     */
    [[nodiscard]] bool isInitialized() const noexcept { return initialized_; }
    
    /**
     * @brief Clear all pending input events
     */
    void clearInput();
    
    /**
     * @brief Enable or disable key repeat for movement actions
     * @param enable True to enable key repeat
     */
    void setKeyRepeatEnabled(bool enable) noexcept { config_.enable_key_repeat = enable; }
    
    /**
     * @brief Check if there are any pending input events
     * @return True if input is available to read
     */
    [[nodiscard]] bool hasInput() const;
    
    /**
     * @brief Wait for any key press (blocking)
     * @return InputState of the pressed key
     */
    [[nodiscard]] InputState waitForInput();
    
    /**
     * @brief Get string representation of an input action (for debugging)
     * @param action The action to convert
     * @return String name of the action
     */
    [[nodiscard]] static const char* actionToString(InputAction action) noexcept;

private:
    Config config_;
    bool initialized_{false};
    
    // Platform-specific implementation details
    struct PlatformData;
    std::unique_ptr<PlatformData> platform_data_;
    
    // Key state tracking for repeat functionality
    struct KeyState {
        bool is_pressed{false};
        std::chrono::steady_clock::time_point press_time;
        std::chrono::steady_clock::time_point last_repeat;
        bool initial_repeat_sent{false};
    };
    
    // Track state for repeatable keys
    KeyState left_key_state_;
    KeyState right_key_state_;
    KeyState down_key_state_;
    
    /**
     * @brief Platform-specific initialization
     * @return True if successful
     */
    bool platformInitialize();
    
    /**
     * @brief Platform-specific shutdown
     */
    void platformShutdown();
    
    /**
     * @brief Platform-specific input polling
     * @return Raw input action without repeat handling
     */
    [[nodiscard]] InputAction platformPollInput();
    
    /**
     * @brief Check if input is available without reading it
     * @return True if input is pending
     */
    [[nodiscard]] bool platformHasInput() const;
    
    /**
     * @brief Convert platform-specific key code to InputAction
     * @param key_code Platform-specific key identifier
     * @return Corresponding InputAction
     */
    [[nodiscard]] InputAction keyCodeToAction(int key_code) const noexcept;
    
    /**
     * @brief Handle key repeat logic for movement actions
     * @param action The input action
     * @param current_time Current timestamp
     * @return InputState with repeat information
     */
    [[nodiscard]] InputState handleKeyRepeat(InputAction action, 
                                           const std::chrono::steady_clock::time_point& current_time);
    
    /**
     * @brief Update key state for repeat tracking
     * @param key_state Reference to key state
     * @param action The action being processed
     * @param current_time Current timestamp
     * @return True if this is a repeat event
     */
    bool updateKeyState(KeyState& key_state, InputAction action, 
                       const std::chrono::steady_clock::time_point& current_time);
    
    /**
     * @brief Reset key state when key is released
     * @param action The action that was released
     */
    void resetKeyState(InputAction action);
    
    /**
     * @brief Check if an action is a repeatable movement action
     * @param action The action to check
     * @return True if action should support key repeat
     */
    [[nodiscard]] static bool isRepeatableAction(InputAction action) noexcept;
};

/**
 * @brief RAII wrapper for input system initialization
 */
class InputSystem {
public:
    /**
     * @brief Initialize input system with default configuration
     */
    InputSystem();
    
    /**
     * @brief Initialize input system with custom configuration
     * @param config Input configuration
     */
    explicit InputSystem(const InputHandler::Config& config);
    
    /**
     * @brief Destructor ensures proper cleanup
     */
    ~InputSystem();
    
    // Non-copyable and non-movable
    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;
    InputSystem(InputSystem&&) = delete;
    InputSystem& operator=(InputSystem&&) = delete;
    
    /**
     * @brief Get the input handler instance
     * @return Reference to the input handler
     */
    [[nodiscard]] InputHandler& getHandler() noexcept { return handler_; }
    
    /**
     * @brief Check if system is ready for input
     * @return True if system is initialized
     */
    [[nodiscard]] bool isReady() const noexcept { return handler_.isInitialized(); }

private:
    InputHandler handler_;
};

} // namespace Tetris
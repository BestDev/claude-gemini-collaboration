#include "Game.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Create and run the Tetris game
        auto game = Tetris::createStandardGame();
        
        if (!game) {
            std::cerr << "Failed to create Tetris game instance" << std::endl;
            return 1;
        }
        
        // Run the game and return its exit code
        return game->run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}
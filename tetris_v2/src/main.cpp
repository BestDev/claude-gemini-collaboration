/**
 * @file main.cpp
 * @brief Entry point for Tetris V2 game
 * 
 * This file contains the main function that initializes and starts the game.
 */

#include <iostream>
#include <exception>
#include "TetrisV2/Game.h"

/**
 * @brief Main entry point for the Tetris V2 application
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return Exit code (0 for success, non-zero for error)
 */
int main(int argc, char* argv[]) {
    try {
        std::cout << "Starting Tetris V2..." << std::endl;
        
        // Create and run the game
        TetrisV2::Game game;
        game.run();
        
        std::cout << "Game exited normally." << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
        
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }
}
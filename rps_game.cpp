#include <iostream>
#include <random>
#include <string>

class RockPaperScissors {
private:
    int playerWins;
    int computerWins;
    int draws;
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;

public:
    RockPaperScissors() : playerWins(0), computerWins(0), draws(0), 
                         generator(std::random_device{}()), distribution(0, 2) {}

    char getComputerChoice() {
        int choice = distribution(generator);
        switch (choice) {
            case 0: return 'r';
            case 1: return 'p';
            case 2: return 's';
            default: return 'r';
        }
    }

    std::string getChoiceName(char choice) {
        switch (choice) {
            case 'r': return "Rock";
            case 'p': return "Paper";
            case 's': return "Scissors";
            default: return "Unknown";
        }
    }

    int determineWinner(char playerChoice, char computerChoice) {
        if (playerChoice == computerChoice) {
            return 0; // Draw
        }
        
        if ((playerChoice == 'r' && computerChoice == 's') ||
            (playerChoice == 'p' && computerChoice == 'r') ||
            (playerChoice == 's' && computerChoice == 'p')) {
            return 1; // Player wins
        }
        
        return -1; // Computer wins
    }

    void playRound() {
        std::string input;
        std::cout << "\nEnter your choice (r = Rock, p = Paper, s = Scissors, q = Quit): ";
        std::cin >> input;

        if (input.length() != 1) {
            std::cout << "Invalid input! Please enter 'r', 'p', 's', or 'q'.\n";
            return;
        }

        char choice = input[0];
        
        if (choice == 'q') {
            showFinalScore();
            exit(0);
        }

        if (choice != 'r' && choice != 'p' && choice != 's') {
            std::cout << "Invalid input! Please enter 'r', 'p', 's', or 'q'.\n";
            return;
        }

        char computerChoice = getComputerChoice();
        
        std::cout << "\nYou chose: " << getChoiceName(choice) << std::endl;
        std::cout << "Computer chose: " << getChoiceName(computerChoice) << std::endl;

        int result = determineWinner(choice, computerChoice);
        
        switch (result) {
            case 1:
                std::cout << "You win this round!" << std::endl;
                playerWins++;
                break;
            case -1:
                std::cout << "Computer wins this round!" << std::endl;
                computerWins++;
                break;
            case 0:
                std::cout << "It's a draw!" << std::endl;
                draws++;
                break;
        }

        showCurrentScore();
    }

    void showCurrentScore() {
        std::cout << "\n--- Current Score ---" << std::endl;
        std::cout << "Player: " << playerWins << std::endl;
        std::cout << "Computer: " << computerWins << std::endl;
        std::cout << "Draws: " << draws << std::endl;
    }

    void showFinalScore() {
        std::cout << "\n=== FINAL SCORE ===" << std::endl;
        std::cout << "Player: " << playerWins << std::endl;
        std::cout << "Computer: " << computerWins << std::endl;
        std::cout << "Draws: " << draws << std::endl;
        std::cout << "\nThank you for playing!" << std::endl;
    }

    void run() {
        std::cout << "=== Rock Paper Scissors Game ===" << std::endl;
        std::cout << "Enter 'r' for Rock, 'p' for Paper, 's' for Scissors, or 'q' to quit." << std::endl;

        while (true) {
            playRound();
        }
    }
};

int main() {
    RockPaperScissors game;
    game.run();
    return 0;
}
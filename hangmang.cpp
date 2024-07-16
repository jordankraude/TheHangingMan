#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>

// Displays different cases for hangman status
void displayHangman(int tries) {
    switch(tries) {
        case 0: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "      |\n"
                           << "      |\n"
                           << "      |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 1: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << "      |\n"
                           << "      |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 2: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << "  |   |\n"
                           << "      |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 3: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << " /|   |\n"
                           << "      |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 4: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << " /|\\  |\n"
                           << "      |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 5: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << " /|\\  |\n"
                           << " /    |\n"
                           << "      |\n"
                           << "=========\n"; break;
        case 6: std::cout << "  -----\n"
                           << "  |   |\n"
                           << "  O   |\n"
                           << " /|\\  |\n"
                           << " / \\  |\n"
                           << "      |\n"
                           << "=========\n"; break;
    }
}

// Function to load words from a file
std::vector<std::string> loadWords(const std::string &filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
        
        // Debugging
        std::cout << "Loaded " << words.size() << " words from " << filename << "\n";
    } else {
        std::cerr << "Unable to open file: " << filename << "\n";
    }
    
    return words;
}

bool playGame(const std::vector<std::string>& words) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Choose a random word from the list
    std::string word = words[std::rand() % words.size()];
    std::string guessed(word.size(), '_');
    std::string wrongGuesses;

    int tries = 0;
    bool win = false;

    while (tries < 6 && !win) {
        std::cout << "Word: " << guessed << "\n";
        displayHangman(tries);
        std::cout << "Wrong guesses: " << wrongGuesses << "\n";
        std::cout << "Enter your guess: ";

        char guess;
        std::cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess) {
                guessed[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            if (wrongGuesses.find(guess) == std::string::npos) {
                wrongGuesses += guess;
                tries++;
            } else {
                std::cout << "You already guessed that letter.\n";
            }
        }

        if (guessed == word) {
            win = true;
        }
    }

    if (win) {
        std::cout << "Congratulations! You guessed the word: " << word << "\n";
    } else {
        displayHangman(6);
        std::cout << "Sorry, you lost. The word was: " << word << "\n";
    }

    char playAgain;
    std::cout << "Do you want to play again? (y/n): ";
    std::cin >> playAgain;

    return playAgain == 'y' || playAgain == 'Y';
}

int main() {
    // DEBUGGING for why not loading file. Print current working directory
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

    // Load words from the file
    std::vector<std::string> words = loadWords("C:/Users/Jordan/Desktop/Workspace/CSE310/TheHangingMan/words.txt");
    if (words.empty()) {
        std::cerr << "No words loaded. Exiting...\n";
        return 1;
    }

    // Play the game and loop if the player wants to play again
    do {
        // Reinitialize variables
    } while (playGame(words));

    return 0;
}

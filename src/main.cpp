#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>   // Required for std::this_thread::sleep_for
#include <chrono>   // Required for duration types

// ANSI colours
#define GREEN  "\033[42m"
#define YELLOW "\033[43m"
#define GRAY   "\033[100m"
#define RESET  "\033[0m"

int turns = 6;

// Load words from file
std::vector<std::string> loadWords() {
    std::vector<std::string> words;
    std::ifstream file("words.txt");

    std::string word;
    while (file >> word) {
        words.push_back(word);
    }

    return words;
}

// Choose random word
std::string chooseWord(const std::vector<std::string>& words) {
    int index = rand() % words.size();
    return words[index];
}

// Check if guess is valid
bool isValid(const std::string& guess, const std::vector<std::string>& words) {
    for (const auto& w : words) {
        if (w == guess) return true;
    }
    return false;
}

// Print result
void printGuess(std::string guess, std::string answer) {

    for (int i = 0; i < 5; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // pause

        if (guess[i] == answer[i]) {
            std::cout << GREEN << " " << (char)toupper(guess[i]) << " " << RESET;
        }
        else if (answer.find(guess[i]) != std::string::npos) {
            std::cout << YELLOW << " " << (char)toupper(guess[i]) << " " << RESET;
        }
        else {
            std::cout << GRAY << " " << (char)toupper(guess[i]) << " " << RESET;
        }
         std::cout << " ";

    }

    std::cout << "\n";
}

int main() {

    srand(time(NULL));

    std::vector<std::string> words = loadWords();

    if (words.empty()) {
        std::cout << "Failed to load words.txt\n";
        return 1;
    }
    while (true) {

        std::string answer = chooseWord(words);

        std::cout << "===== TERMINAL WORDLE =====\n";
        std::cout << "Guess the 5 letter word!\n\n";

        for (int attempt = 1; attempt <= turns; attempt++) {

            std::string guess;

            std::cout << "Guess " << attempt << "/" << turns << ": ";
            std::cin >> guess;

            std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower); // clean

            if (guess.length() != 5) {
                std::cout << "Word must be 5 letters.\n";
                attempt--;
                continue;
            }

            if (!isValid(guess, words)) {
                std::cout << "Not in word list.\n";
                attempt--;
                continue;
            }

            printGuess(guess, answer);

            //words.erase(std::remove(words.begin(), words.end(), guess), words.end());
            //std::cout << "Removed guessed word\n\n";
            

            if (guess == answer) {
                std::cout << "\n You guessed it!\n";
                return 0;
            }

        }
        std::cout << "\nYou lost! The word was: " << answer << "\n";

    }

    return 0;
}
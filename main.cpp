#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to generate a random code
std::vector<int> generateCode(int length, int maxDigit) {
    std::vector<int> code(length);
    for (int i = 0; i < length; ++i) {
        code[i] = rand() % (maxDigit + 1);
    }
    return code;
}

// Function to get player's guess
std::vector<int> getGuess(int length) {
    std::vector<int> guess(length);
    std::cout << "Enter your guess: ";
    for (int i = 0; i < length; ++i) {
        std::cin >> guess[i];
    }
    return guess;
}

// Function to give feedback on the guess
void giveFeedback(const std::vector<int>& code, const std::vector<int>& guess) {
    int correctPosition = 0;
    int correctDigit = 0;
    std::vector<bool> codeUsed(code.size(), false);
    std::vector<bool> guessUsed(guess.size(), false);

    // Check for correct positions
    for (size_t i = 0; i < code.size(); ++i) {
        if (code[i] == guess[i]) {
            ++correctPosition;
            codeUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    // Check for correct digits in wrong positions
    for (size_t i = 0; i < code.size(); ++i) {
        if (!guessUsed[i]) {
            for (size_t j = 0; j < code.size(); ++j) {
                if (!codeUsed[j] && guess[i] == code[j]) {
                    ++correctDigit;
                    codeUsed[j] = true;
                    break;
                }
            }
        }
    }

    std::cout << "Correct positions: " << correctPosition << "\n";
    std::cout << "Correct digits (wrong positions): " << correctDigit << "\n";
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed random number generator

    const int codeLength = 4;
    const int maxDigit = 6;  // Digits range from 0 to 6
    const int maxAttempts = 10;

    std::vector<int> code = generateCode(codeLength, maxDigit);

    std::cout << "Welcome to Mastermind!\n";
    std::cout << "Try to guess the " << codeLength << "-digit code.\n";
    std::cout << "Digits are between 0 and " << maxDigit << ".\n";

    for (int attempt = 1; attempt <= maxAttempts; ++attempt) {
        std::cout << "Attempt " << attempt << " of " << maxAttempts << ":\n";
        std::vector<int> guess = getGuess(codeLength);

        if (guess == code) {
            std::cout << "Congratulations! You've guessed the code.\n";
            return 0;
        } else {
            giveFeedback(code, guess);
        }
    }

    std::cout << "Sorry, you've used all your attempts. The code was: ";
    for (size_t i = 0; i < code.size(); ++i) {
        std::cout << code[i] << " ";
    }
    std::cout << "\n";

    return 0;
}

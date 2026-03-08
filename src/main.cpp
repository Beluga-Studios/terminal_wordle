#include <iostream>
#include <string>

int main() {
    std::cout << "termwordle - Terminal Game" << std::endl;

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "quit") break;

        std::cout << "You typed: " << input << std::endl;
    }

    return 0;
}

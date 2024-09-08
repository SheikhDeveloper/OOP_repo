#include <iostream>
#include <limits>

template<typename T> void valid_input(T &variable) {
    std::cin >> variable;
    while (std::cin.fail()) {
        std::cout << "Invalid input." << std::endl;
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> variable;
    }
}

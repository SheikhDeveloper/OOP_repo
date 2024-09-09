#include <iostream>
#include <limits>

template<typename T> bool valid_input(T &variable) {
    std::cin >> variable;
    if (std::cin.eof()) return 1;
    while (std::cin.fail()) {
        if (std::cin.eof()) return EOF;
        std::cout << "Invalid input." << std::endl;
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> variable;
    }
    return 0;
}

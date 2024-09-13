#ifndef LAB1_LIB_UTILS_HPP
#define LAB1_LIB_UTILS_HPP

#include <iostream>
#include <limits>

/**
 * @brief Reads input from the standard input stream and validates it.
 * 
 * This function reads input from the standard input stream and attempts to store 
 * it in the provided variable. If the input is invalid (e.g., non-numeric input 
 * when reading into a numeric variable), the function will prompt the user to 
 * re-enter the input until valid input is provided.
 * 
 * If the end of the input stream is reached, the function will return 1. If the 
 * input is successfully read, the function will return 0.
 * 
 * @tparam T The type of variable to read input into.
 * @param variable The variable to store the input in.
 * @return 0 if the input was successfully read, 1 if the end of the input stream 
 * was reached.
 */
template<typename T> bool valid_input(T &variable) {
    std::cin >> variable;
    if (std::cin.eof()) return 1;
    while (std::cin.fail()) {
        if (std::cin.eof()) return 1;
        std::cout << "Invalid input." << std::endl;
        std::cout << "Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> variable;
    }
    return 0;
}

#endif

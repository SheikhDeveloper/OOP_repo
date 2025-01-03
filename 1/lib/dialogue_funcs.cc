#include "dialogue_funcs.hpp"
#include "utils.hpp"

#include <iostream>
#include <algorithm>
#include <cstring>

using std::cout;
using std::string;
using std:: cin;
using std::cerr;

const char *menu_items[5]{"Specify string type[0-const char*/1-std::string]: ",
                          "Do you want your string to have fixed size?[0-N/1-Y]: ",
                           "Input string size: ",
                           "Input string: ",
                           "Specify action to perform on string[0-decode/1-encode]: "};

bool choose_action(TEncoder &encoder) {
    cout << menu_items[4];
    bool encode;
    auto eof = valid_input<bool>(encode);
    if (eof) return 1;
    eof = choose_string_type(encoder, encode);
    return eof;
}

bool choose_string_type(TEncoder &encoder, bool encode) {
    bool type;
    cout << menu_items[0];
    auto eof = valid_input<bool>(type); 
    if (eof) return 1;
    if (type) eof = dialogue_action_on_string(encoder, encode);
    else eof = dialogue_action_on_c_string(encoder, encode);
    return eof;
}

bool dialogue_action_on_string(TEncoder &encoder, bool encode) {
    string input;
    cout << menu_items[3];
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(cin, input);
    string output;
    if (encode) output = encoder.encode(input);
    else output = encoder.decode(input);
    if (output.size() > 0) {
        cout << output << std::endl;
    }
    else cerr << "Error: Invalid string passed to decoder" << std::endl;
    return 0;
}

bool dialogue_action_on_c_string(TEncoder &encoder, bool encode) {
    cout << menu_items[1];
    bool fixed_size;
    auto eof = valid_input<bool>(fixed_size);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (eof) return 1;
    if (fixed_size) eof = dialogue_action_on_char_array(encoder, encode);
    else {
        eof = 0;
        std::string str_input;
        cout << menu_items[3];
        std::getline(cin, str_input);
        auto input = str_input.c_str();
        const char *output;
        if (encode) output = encoder.encode(input);
        else output = encoder.decode(input);
        if (strlen(output) > 0) {
            cout << output << std::endl;
        }
        else cerr << "Error: Invalid string passed to decoder" << std::endl;
        delete [] output;
    }
    return eof;
}

bool dialogue_action_on_char_array(TEncoder &encoder, bool encode) {
    size_t array_size;
    cout << menu_items[2];
    bool eof = valid_input(array_size);
    if (eof) return 1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto array = new char[array_size];
    string input;
    cout << menu_items[3];
    std::getline(cin, input);
    std::copy_if(input.begin(), input.end(), array, 
                 [](char x) { return x != 0; });
    std::pair<const char *, size_t> output;
    if (encode) output = encoder.encode(array, array_size);
    else output = encoder.decode(array, array_size);
    auto resulting_inp = output.first;
    auto resulting_size = output.second;
    delete [] array;
    if (resulting_size > 0) {
        for (size_t i = 0; i < resulting_size; i++) {
            cout << resulting_inp[i];
        }
    }
    else cerr << "Error: Invalid string passed to decoder" << std::endl;
    delete [] resulting_inp;
    cout << std::endl;
    return 0;
}

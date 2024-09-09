#include "dialogue_funcs.hpp"
#include "utils.hpp"

#include <iostream>

using std::cout;
using std::string;
using std:: cin;

const char *menu_items[5]{"Specify string type[0-const char*/1-std::string]: ",
                          "Do you want your string to have fixed size?[0-N/1-Y]: ",
                           "Input string size: ",
                           "Input string: ",
                           "Specify action to perform on string[0-decode/1-encode]: "};

bool choose_action(TEncoder &encoder) {
    cout << menu_items[4];
    bool encode;
    bool eof = valid_input<bool>(encode);
    if (eof) return 1;
    eof = choose_string_type(encoder, encode);
    return eof;
}

bool choose_string_type(TEncoder &encoder, bool encode) {
    bool type;
    cout << menu_items[0];
    bool eof = valid_input<bool>(type); 
    if (eof) return 1;
    if (type) eof = dialogue_action_on_string(encoder, encode);
    else eof = dialogue_action_on_c_string(encoder, encode);
    return eof;
}

bool dialogue_action_on_string(TEncoder &encoder, bool encode) {
    string input;
    cout << menu_items[3];
    bool eof = valid_input<string>(input);
    if (eof) return 1;
    string output;
    if (encode) output = encoder.encode(input);
    else output = encoder.decode(input);
    cout << output << std::endl;
    return 0;
}

bool dialogue_action_on_c_string(TEncoder &encoder, bool encode) {
    cout << menu_items[1];
    bool fixed_size;
    bool eof = valid_input<bool>(fixed_size);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (eof) return 1;
    if (fixed_size) eof = dialogue_action_on_char_array(encoder, encode);
    else {
        eof = 0;
        std::string str_input;
        cout << menu_items[3];
        std::getline(cin, str_input);
        const char *input = str_input.c_str();
        char *output;
        if (encode) output = encoder.encode(input);
        else output = encoder.decode(input);
        cout << output << std::endl;
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
    char *array = new char[array_size];
    string input;
    cout << menu_items[3];
    std::getline(cin, input);
    for (size_t i = 0; i < array_size; i++) {
        array[i] = input[i];
    }    
    std::pair<char *, size_t> output;
    if (encode) output = encoder.encode(array, array_size);
    else output = encoder.decode(array, array_size);
    auto encoded_inp = output.first;
    auto encoded_size = output.second;
    delete [] array;
    for (size_t i = 0; i < encoded_size; i++) {
        cout << encoded_inp[i];
    }
    cout << std::endl;
    delete [] encoded_inp;
    return 0;
}

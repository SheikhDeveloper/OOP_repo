#include "dialogue_funcs.hpp"
#include "utils.hpp"

#include <iostream>

using std::cout;
using std::string;

const char *menu_items[5]{"Specify string type[0-const char*/1-std::string]: ",
                          "Do you want your string to have fixed size?[Y/n]: ",
                           "Input string size: ",
                           "Input string: "};

void choose_string_type(TEncoder &encoder) {
    bool type;
    cout << menu_items[0];
    valid_input<bool>(type); 
    if (type) dialogue_encode_string(encoder);
    else dialogue_encode_c_string(encoder);
}

void dialogue_encode_string(TEncoder &encoder) {
    string input;
    cout << menu_items[3];
    valid_input<string>(input);
    string encoded_input = encoder.encode(input);
    cout << encoded_input << std::endl;
}

void dialogue_encode_c_string(TEncoder &encoder) {
    cout << menu_items[1];
    char fixed_size;
    valid_input<char>(fixed_size);
}

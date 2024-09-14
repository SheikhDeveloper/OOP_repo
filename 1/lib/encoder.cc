#include "encoder.hpp"

#include <sstream>
#include <algorithm>

using std::string;
using std::pair;

char *TEncoder::encode(const char *input) {
    std::stringstream encoding_stream;
    for (const char *c = input; *c != 0; c++) {
        if (!isalpha(*c) && !isdigit(*c) && *c != '-' && *c != '_') {
            encoding_stream << "%" << std::uppercase << std::hex << static_cast<int>(*c);
        }
        else encoding_stream << std::dec << *c;
    }
    string encoded_inp_str = encoding_stream.str();
    char *encoded_input = new char[encoded_inp_str.size() + 1];
    const char *encoded_inp_c_str = encoded_inp_str.c_str();
    std::copy(encoded_inp_c_str, encoded_inp_c_str + encoded_inp_str.size() + 1, encoded_input);
    return encoded_input;
}    

pair<char *, size_t> TEncoder::encode(const char *input, size_t input_size) {
    std::stringstream encoding_stream;
    for (size_t i= 0; i < input_size; i++) {
        if (!isalpha(input[i]) && !isdigit(input[i]) && input[i] != '-' && input[i] != '_') {
            encoding_stream << "%" << std::uppercase << std::hex << static_cast<int>(input[i]);
        }
        else encoding_stream << std::dec << input[i];
    }
    string encoded_inp_str = encoding_stream.str();
    size_t encoded_inp_size = encoded_inp_str.size();
    char *encoded_input = new char[encoded_inp_size];
    std::copy_if(encoded_inp_str.begin(), encoded_inp_str.end(), encoded_input, 
                 [](char x) { return x != 0; });
    return {encoded_input, encoded_inp_size};
}

string TEncoder::encode(string input) {
    std::stringstream encoding_stream;
    for (auto c : input) {
        if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_') {
            encoding_stream << "%" << std::uppercase << std::hex << static_cast<int>(c);
        }
        else encoding_stream << std::dec << c;
    }
    return encoding_stream.str();
}

char *TEncoder::decode(const char *input) {
    std::stringstream decoded_input;
    size_t cur_state = 0;
    std::stringstream hex_string;
    for (const char *c = input; *c != 0; c++) {
        if (cur_state == 0) {
            if (*c == '%') {
                cur_state = 1;
            }
            else if ((*c < 'A' && *c != '-') || (*c > 'Z' && *c < 'a' && *c != '_') || (*c > 'z')) { 
                try { throw std::runtime_error("Invalid string passed to decoder"); } 
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            else decoded_input << *c;
        }
        else if (cur_state == 1) {
            if (('0' <= *c && *c <= '9') || ('A' <= *c && *c <= 'F')) {
                cur_state = 2;
                hex_string << *c;
            }
            else {
                cur_state = 0;
                hex_string.str("");
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
        }
        else if (cur_state == 2) {
            if (('0' <= *c && *c <= '9') || ('A' <= *c && *c <= 'F')) {
                hex_string << *c;
                char ascii_char = static_cast<char>(stoul(hex_string.str(), nullptr, 16));
                decoded_input << ascii_char;
            }
            else {
                try {throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            hex_string.str("");
            cur_state = 0;
        }
    }
    string result_str = decoded_input.str();
    char *result = new char[result_str.size() + 1];
    const char *result_c_str = result_str.c_str();
    std::copy(result_c_str, result_c_str + result_str.size() + 1, result);
    return result;
}    

pair<char *, size_t> TEncoder::decode(const char *input, size_t input_size) {
    std::stringstream decoded_input;
    size_t cur_state = 0;
    std::stringstream hex_string;
    for (size_t i = 0; i < input_size; i++) {
        if (cur_state == 0) {
            if (input[i] == '%') {
                cur_state = 1;
            }
            else if ((input[i] < 'A' && input[i] != '-') || (input[i] > 'Z' && input[i] < 'a' && input[i] != '_') || (input[i] > 'z')) { 
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            else decoded_input << input[i];
        }
        else if (cur_state == 1) {
            if (('0' <= input[i] && input[i] <= '9') || ('A' <= input[i] && input[i] <= 'F')) {
                cur_state = 2;
                hex_string << input[i];
            }
            else {
                cur_state = 0;
                hex_string.str("");
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
        }
        else if (cur_state == 2) {
            if (('0' <= input[i] && input[i] <= '9') || ('A' <= input[i] && input[i] <= 'F')) {
                hex_string << input[i];
                char ascii_char = static_cast<char>(stoul(hex_string.str(), nullptr, 16));
                decoded_input << ascii_char;
            }
            else {
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            hex_string.str("");
            cur_state = 0;
        }
    }
    string result_str = decoded_input.str();
    size_t result_size = result_str.size();
    char *result = new char[result_size];
    std::copy_if(result_str.begin(), result_str.end(), result,
            [](char x) { return x != 0; } );
    return {result, result_size};
}

string TEncoder::decode(string input) {
    std::stringstream decoded_input;
    size_t cur_state = 0;
    std::stringstream hex_string;
    for (auto c : input) {
        if (cur_state == 0) {
            if (c == '%') {
                cur_state = 1;
            }
            else if ((c < 'A' && c != '-') || (c > 'Z' && c < 'a' && c != '_') || (c > 'z')) {
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            else decoded_input << c;
        }
        else if (cur_state == 1) {
            if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F')) {
                cur_state = 2;
                hex_string << c;
            }
            else {
                cur_state = 0;
                hex_string.str("");
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
        }
        else if (cur_state == 2) {
            if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F')) {
                hex_string << c;
                char ascii_char = static_cast<char>(stoul(hex_string.str(), nullptr, 16));
                decoded_input << ascii_char;
            }
            else {
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            hex_string.str("");
            cur_state = 0;
        }
    }
    return decoded_input.str();
}

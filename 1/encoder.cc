#include "encoder.hpp"

#include <string>
#include <sstream>
#include <algorithm>
#include <regex>

using std::pair;
using std::string;
using std::regex;

struct _tencoder {
    char *encode(const char *input) {
        std::stringstream encoding_stream;
        for (const char *c = input; *c != 0; c++) {
            if (!isalpha(*c) && !isdigit(*c) && *c != '-' && *c != '_') {
                encoding_stream << "%" << std::hex << *c;
            }
            else encoding_stream << std::dec << *c;
        }
        string encoded_inp_str = encoding_stream.str();
        char *encoded_input = encoded_inp_str.data();
        return encoded_input;
    }    
    pair<char *, size_t> encode(const char *input, size_t input_size) {
        std::stringstream encoding_stream;
        for (size_t i= 0; i < input_size; i++) {
            if (!isalpha(input[i]) && !isdigit(input[i]) && input[i] != '-' && input[i] != '_') {
                encoding_stream << "%" << std::hex << input[i];
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
    string encode(string input) {
        std::stringstream encoding_stream;
        for (auto c : input) {
            if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_') {
                encoding_stream << "%" << std::hex << c;
            }
            else encoding_stream << std::dec << c;
        }
        return encoding_stream.str();
    }
    char *decode(const char *input) {
        std::stringstream decoded_input;
        size_t cur_state = 0;
        std::stringstream hex_string;
        for (const char *c = input; *c != 0; c++) {
            if (cur_state == 0) {
                if (*c == '%') {
                    cur_state = 1;
                }
                else decoded_input << *c;
            }
            else if (cur_state == 1) {
                if ('0' < *c && *c < '9') {
                    cur_state = 2;
                    hex_string << *c;
                }
                else {
                    cur_state = 0;
                    hex_string.flush();
                }
            }
            else if (cur_state == 2) {
                if ('0' < *c && *c < '9') {
                    hex_string << *c;
                    decoded_input << std::dec << hex_string.str();
                }
                hex_string.flush();
                cur_state = 0;
            }
        }
        string result_str = decoded_input.str();
        char *result = result_str.data();
        return result;
    }    
    pair<const char *, size_t> decode(const char *input, size_t input_size) {
        std::stringstream decoded_input;
        size_t cur_state = 0;
        std::stringstream hex_string;
        for (size_t i = 0; i < input_size; i++) {
            if (cur_state == 0) {
                if (input[i] == '%') {
                    cur_state = 1;
                }
                else decoded_input << input[i];
            }
            else if (cur_state == 1) {
                if ('0' < input[i] && input[i] < '9') {
                    cur_state = 2;
                    hex_string << input[i];
                }
                else {
                    cur_state = 0;
                    hex_string.flush();
                }
            }
            else if (cur_state == 2) {
                if ('0' < input[i] && input[i] < '9') {
                    hex_string << input[i];
                    decoded_input << std::dec << hex_string.str();
                }
                hex_string.flush();
                cur_state = 0;
            }
        }
        string result_str = decoded_input.str();
        size_t result_size = result_str.size();
        char *result;
        std::copy_if(result_str.begin(), result_str.end(), result,
                [](char x) { return x != 0; } );
        return {result, result_size};
    }
    string decode(string input) {
        std::stringstream decoded_input;
        size_t cur_state = 0;
        std::stringstream hex_string;
        for (auto c : input) {
            if (cur_state == 0) {
                if (c == '%') {
                    cur_state = 1;
                }
                else decoded_input << c;
            }
            else if (cur_state == 1) {
                if ('0' < c && c < '9') {
                    cur_state = 2;
                    hex_string << c;
                }
                else {
                    cur_state = 0;
                    hex_string.flush();
                }
            }
            else if (cur_state == 2) {
                if ('0' < c && c < '9') {
                    hex_string << c;
                    decoded_input << std::dec << hex_string.str();
                }
                hex_string.flush();
                cur_state = 0;
            }
        }
        return decoded_input.str();
    }

};

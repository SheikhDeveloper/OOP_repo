#include "encoder.hpp"

#include <string>
#include <sstream>
#include <algorithm>

using std::pair;
using std::string;

struct _tencoder {
    char *encode(const char *input) {
        std::stringstream encoding_stream;
        for (char c = *input; c != 0; c++) {
            if (!isalpha(c) && !isdigit(c) && c != '-' && c != '_') {
                encoding_stream << "%" << std::hex << c;
            }
            else encoding_stream << std::dec << c;
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

    }    
    pair<const char *, size_t> *decode(const char *input, size_t input_size) {

    }
    string decode(string input) {

    }

};

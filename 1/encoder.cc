#include "encoder.hpp"

#include <string>
#include <cstring>
//#include <algorithm>

using std::string;
using std::pair;

struct TEncoder {
    char *encode(const char *input) {
        char *encoded_input = new char[3 * strlen(input)];
        return encoded_input;
    }    
    pair<char *, size_t> *encode(const char *input, size_t input_size) {

    }
    string encode(string input) {

    }
    char *decode(const char *input) {

    }    
    pair<const char *, size_t> *decode(const char *input, size_t input_size) {

    }
    string decode(string input) {

    }
};

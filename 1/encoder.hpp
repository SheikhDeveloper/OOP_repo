#ifndef LAB1_ENCODER_HPP
#define LAB1_ENCODER_HPP

#include <string>

using std::pair;
using std::string;

typedef struct _tencoder {
    char *encode(const char *input);
    pair<char *, size_t> encode(const char *input, size_t input_size);
    string encode(string input);
    char *decode(const char *input);
    pair<const char *, size_t> decode(const char *input, size_t input_size);
    string decode(string input);
} TEncoder;

#endif

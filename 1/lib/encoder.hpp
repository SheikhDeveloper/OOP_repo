#ifndef LAB1_ENCODER_HPP
#define LAB1_ENCODER_HPP

#include <string>

typedef struct _tencoder {
    char *encode(const char *input);
    std::pair<char *, size_t> encode(const char *input, size_t input_size);
    std::string encode(std::string input);
    char *decode(const char *input);
    std::pair<char *, size_t> decode(const char *input, size_t input_size);
    std::string decode(std::string input);
} TEncoder;

#endif

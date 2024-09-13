#ifndef LAB1_LIB_ENCODER_HPP
#define LAB1_LIB_ENCODER_HPP

#include <string>

/**
 * @brief A struct representing an encoder.
 * 
 * This struct contains functions for encoding and decoding strings using a url 
 * encoding scheme.
 */
typedef struct _tencoder {

/**
 * @brief Encodes a null-terminated C-style string using a url encoding scheme.
 * 
 * This function takes a null-terminated C-style string as input and returns a new 
 * C-style string with the encoded result. The encoding scheme replaces non-alphanumeric 
 * characters with their corresponding hexadecimal escape sequences.
 * 
 * @param input The null-terminated C-style string to be encoded.
 * @return A new C-style string containing the encoded result.
 */
    char *encode(const char *input);

/**
 * @brief Encodes a C-style string of a specified length using a url encoding scheme.
 * 
 * This function takes a C-style string and its length as input, and returns a pair 
 * containing the encoded result as a C-style string and its length.
 * 
 * The encoding scheme replaces non-alphanumeric characters with their corresponding 
 * hexadecimal escape sequences.
 * 
 * @param input The C-style string to be encoded.
 * @param input_size The length of the input string.
 * @return A pair containing the encoded result as a C-style string and its length.
 */
    std::pair<char *, size_t> encode(const char *input, size_t input_size);

/**
 * @brief Encodes a C++ string using a url encoding scheme.
 * 
 * This function takes a C++ string as input and returns a new C++ string with the 
 * encoded result. The encoding scheme replaces non-alphanumeric characters with their 
 * corresponding hexadecimal escape sequences.
 * 
 * @param input The C++ string to be encoded.
 * @return A new C++ string containing the encoded result.
 */
    std::string encode(std::string input);

/**
 * @brief Decodes a null-terminated C-style string that was previously encoded using 
 * the url encoding scheme.
 * 
 * This function takes a null-terminated C-style string as input and returns a new 
 * C-style string with the decoded result.
 * 
 * @param input The null-terminated C-style string to be decoded.
 * @return A new C-style string containing the decoded result.
 */
    char *decode(const char *input);

/**
 * @brief Decodes a C-style string of a specified length that was previously encoded 
 * using the url encoding scheme.
 * 
 * This function takes a C-style string and its length as input, and returns a pair 
 * containing the decoded result as a C-style string and its length.
 * 
 * @param input The C-style string to be decoded.
 * @param input_size The length of the input string.
 * @return A pair containing the decoded result as a C-style string and its length.
 */
    std::pair<char *, size_t> decode(const char *input, size_t input_size);

/**
 * @brief Decodes a C++ string that was previously encoded using the url encoding scheme.
 * 
 * This function takes a C++ string as input and returns a new C++ string with the 
 * decoded result.
 * 
 * @param input The C++ string to be decoded.
 * @return A new C++ string containing the decoded result.
 */
    std::string decode(std::string input);
} TEncoder;

#endif

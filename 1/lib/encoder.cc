#include "encoder.hpp"

#include <sstream>
#include <algorithm>

using std::string;
using std::pair;

const char *TEncoder::encode(const char *input) {
    auto encoded = TEncoder::encode(string(input));
    auto result = new char[encoded.size() + 1];
    std::copy(encoded.begin(), encoded.end(), result);
    result[encoded.size()] = 0;
    return result;
}    

pair<const char *, size_t> TEncoder::encode(const char *input, size_t input_size) {
    auto encoded = TEncoder::encode(string(input, input_size));;
    auto result = new char[encoded.size()];
    auto result_size = encoded.size();
    std::copy(encoded.begin(), encoded.end(), result);
    return {result, result_size};
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

const char *TEncoder::decode(const char *input) {
    auto decoded = TEncoder::decode(string(input));
    auto result = new char[decoded.size() + 1];
    std::copy(decoded.begin(), decoded.end() + 1, result);
    return result;
}    

pair<const char *, size_t> TEncoder::decode(const char *input, size_t input_size) {
    auto decoded = TEncoder::decode(string(input, input_size));
    auto result = new char[decoded.size()];
    auto result_size = decoded.size();
    std::copy(decoded.begin(), decoded.end(), result);
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
            else if (!isalnum(c) && c != '-' && c != '_') {
                try { throw std::runtime_error("Invalid string passed to decoder"); }
                catch (const std::runtime_error& e) {
                    decoded_input.str("");
                    break;
                }
            }
            else decoded_input << c;
        }
        else if (cur_state == 1) {
            if (isdigit(c) || ('A' <= c && c <= 'F')) {
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
            if (isdigit(c) || ('A' <= c && c <= 'F')) {
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

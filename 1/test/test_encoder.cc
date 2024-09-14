#include "../lib/encoder.hpp"
#include "gtest/gtest.h"

TEST(TEncoderTest, EncodeCharPtr) {
    TEncoder encoder;
    const char* input = "Hello, World!";
    char* encoded = encoder.encode(input);
    EXPECT_STREQ(encoded, "Hello%2C%20World%21");
    delete[] encoded;
}

TEST(TEncoderTest, EncodeCharPtrWithSize) {
    TEncoder encoder;
    const char* input = "Hello, World!";
    size_t inputSize = strlen(input);
    auto encoded = encoder.encode(input, inputSize);
    const char* test_str = "Hello%2C%20World%21";
    EXPECT_EQ(encoded.second, strlen(test_str));
    for (size_t i = 0; i < encoded.second; ++i) {
      EXPECT_EQ(encoded.first[i], test_str[i]);
    }
    delete[] encoded.first;
}

TEST(TEncoderTest, EncodeStdString) {
    TEncoder encoder;
    std::string input = "Hello, World!";
    std::string encoded = encoder.encode(input);
    EXPECT_EQ(encoded, "Hello%2C%20World%21");
}

TEST(TEncoderTest, DecodeCharPtr) {
    TEncoder encoder;
    const char* input = "Hello%2C%20World%21";
    char* decoded = encoder.decode(input);
    EXPECT_STREQ(decoded, "Hello, World!");
    delete[] decoded;
}

TEST(TEncoderTest, DecodeCharPtrWithSize) {
    TEncoder encoder;
    const char* input = "Hello%2C%20World%21";
    size_t inputSize = strlen(input);
    auto decoded = encoder.decode(input, inputSize);
    const char *test_str = "Hello, World!";
    EXPECT_EQ(decoded.second, strlen(test_str));
    for (size_t i = 0; i < decoded.second; ++i) {
      EXPECT_EQ(decoded.first[i], test_str[i]);
    }
    delete[] decoded.first;
}

TEST(TEncoderTest, DecodeStdString) {
    TEncoder encoder;
    std::string input = "Hello%2C%20World%21";
    std::string decoded = encoder.decode(input);
    EXPECT_EQ(decoded, "Hello, World!");
}

TEST(TEncoderTest, EncodeDecodeCharPtr) {
    TEncoder encoder;
    const char* input = "Hello, World!";
    char* encoded = encoder.encode(input);
    char* decoded = encoder.decode(encoded);
    EXPECT_STREQ(decoded, input);
    delete[] encoded;
    delete[] decoded;
}

TEST(TEncoderTest, EncodeDecodeCharPtrWithSize) {
    TEncoder encoder;
    const char* input = "Hello, World!";
    size_t inputSize = strlen(input);
    auto encoded = encoder.encode(input, inputSize);
    auto decoded = encoder.decode(encoded.first, encoded.second);
    EXPECT_EQ(decoded.second, inputSize);
    for (size_t i = 0; i < decoded.second; ++i) {
      EXPECT_EQ(decoded.first[i], input[i]);
    } 
    delete[] encoded.first;
    delete[] decoded.first;
}

TEST(TEncoderTest, EncodeDecodeStdString) {
    TEncoder encoder;
    std::string input = "Hello, World!";
    std::string encoded = encoder.encode(input);
    std::string decoded = encoder.decode(encoded);
    EXPECT_EQ(decoded, input);
}

TEST(TEncoderTest, InvalidDecodeCharPtr) {
    TEncoder encoder;
    const char* input = "Invalid%Input";
    char* decoded = encoder.decode(input);
    EXPECT_STREQ(decoded, "");
    delete[] decoded;
}

TEST(TEncoderTest, InvalidDecodeCharPtrWithSize) {
    TEncoder encoder;
    const char* input = "Invalid%Input";
    size_t inputSize = strlen(input);
    auto decoded = encoder.decode(input, inputSize);
    EXPECT_EQ(decoded.second, 0);
    delete[] decoded.first;
}

TEST(TEncoderTest, InvalidDecodeStdString) {
    TEncoder encoder;
    std::string input = "Invalid%Input";
    std::string decoded = encoder.decode(input);
    EXPECT_EQ(decoded, "");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

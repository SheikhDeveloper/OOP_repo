include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_encoder test_encoder.cc)

target_link_libraries(test_encoder PRIVATE gtest gtest_main encoder)

add_test(NAME TestEncoder COMMAND EncoderTest)

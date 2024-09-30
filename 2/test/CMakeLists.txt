enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_hash_table test_hash_table.cc)

add_library(hash_table ../lib/hash_table.h)

target_link_libraries(test_hash_table PRIVATE gtest gtest_main)
target_link_libraries(test_hash_table PRIVATE hash_table)

add_test(NAME test_hash_table COMMAND test_hash_table)

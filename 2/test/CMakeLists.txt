enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

option(GET_COVERAGE "Run tests with code coverage" ON)
option(GET_COVERAGE "Run tests without code coverage" OFF)

if(GET_COVERAGE)


add_executable(test_hash_table test_hash_table.cc)
add_executable(test_cocktail_card test_cocktail_card.cc)
add_executable(test_cocktail test_cocktail.cc)

target_link_libraries(test_hash_table PRIVATE gtest gtest_main)
target_link_libraries(test_cocktail_card PRIVATE gtest gtest_main)
target_link_libraries(cocktail_card PRIVATE cocktail)
target_link_libraries(test_cocktail_card PRIVATE cocktail_card)
target_link_libraries(test_cocktail PRIVATE cocktail)
target_link_libraries(test_cocktail PRIVATE gtest gtest_main)


add_test(NAME test_hash_table COMMAND test_hash_table)
add_test(NAME test_cocktail COMMAND test_cocktail)
add_test(NAME test_cocktail_card COMMAND test_cocktail_card)

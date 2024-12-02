enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_hash_table test_hash_table.cc)
add_executable(test_non_container test_non_container.cc)
add_executable(test_container test_container.cc)

target_link_libraries(test_hash_table PRIVATE gtest gtest_main)
target_link_libraries(test_non_container PRIVATE gtest gtest_main)
target_link_libraries(test_container PRIVATE gtest gtest_main)
target_link_libraries(battleship PRIVATE weaponry)
target_link_libraries(battleship PRIVATE plane)
target_link_libraries(battleship PRIVATE plane_group)
target_link_libraries(test_non_container PRIVATE battleship plane weaponry)
target_link_libraries(test_container PRIVATE battleship_group plane_group)


add_test(NAME test_non_container COMMAND test_non_container)
add_test(NAME test_container COMMAND test_container)
add_test(NAME test_hash_table COMMAND test_hash_table)

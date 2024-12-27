include_directories(${sfml_SOURCE_DIR}/include ${sfml_SOURCE_DIR})

add_executable(app ctx_draw_functions.cc)

add_library(input_field input_field.cc)

target_link_libraries(app PRIVATE input_field)
target_link_libraries(app PRIVATE battleship_group plane_group)
target_link_libraries(app PRIVATE sfml-graphics sfml-window sfml-system)



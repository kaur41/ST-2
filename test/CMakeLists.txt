add_executable(${PROJECT_NAME}.test
    tests.cpp)

target_link_libraries(${PROJECT_NAME}.test
    ${PROJECT_NAME}
    gtest_main)

target_compile_definitions(${PROJECT_NAME}.test 
    PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}")

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}.test)

install(TARGETS ${PROJECT_NAME}.test
    RUNTIME DESTINATION "${tool_dest}")
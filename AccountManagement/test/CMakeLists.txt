enable_testing()

# 收集所有源文件
file(GLOB_RECURSE TEST_SOURCES 
    "${PROJECT_SOURCE_DIR}/src/core/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/data/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/stats/*.cpp"
)

# 移除main.cpp
list(FILTER TEST_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

add_executable(account_tests
    test_main.cpp
    ${TEST_SOURCES}
)

target_include_directories(account_tests PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)

# 链接Google Test
target_link_libraries(account_tests
    gtest
    gtest_main
    pthread
)

add_test(NAME account_tests COMMAND account_tests)
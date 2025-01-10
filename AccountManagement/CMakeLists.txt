cmake_minimum_required(VERSION 3.10)
project(AccountManagement VERSION 1.0)

# 添加构建选项
option(BUILD_TESTS "Build test cases" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 包含目录
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 可执行文件
add_executable(account_manager ${SOURCES})

# 条件编译测试
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
    message(STATUS "Building with tests enabled")
else()
    message(STATUS "Building without tests")
endif()
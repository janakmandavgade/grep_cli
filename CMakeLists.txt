cmake_minimum_required(VERSION 3.14)
project(grep_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- GoogleTest Setup ---
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)
find_package(GTest REQUIRED)
include(GoogleTest)

enable_testing()

# --- Project Configuration ---

# 1. Include headers directory
include_directories(headers)

# 2. Create the core logic library
add_library(logic 
    # src/errors
    # src/main.cpp
    src/utils.cpp
)

# 3. Create the main application executable
add_executable(mygrep main.cpp)
target_link_libraries(mygrep logic)

# 4. Create the test executable
# add_executable(tests 
#     # tests/test_utils.cpp
# )
# target_link_libraries(tests 
#     logic 
#     GTest::gtest_main
# )

# --- Discover Tests ---
# # include(GoogleTest)
# gtest_discover_tests(tests)
cmake_minimum_required(VERSION 3.26)
project(MyGraphTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        MyGraphTest
        graphListTest.cpp
        MatrixTest.cpp
        graphMatrixTest.cpp

        ../src/Utils.cpp
        ../src/Logger.cpp
)

target_link_libraries(
        MyGraphTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyGraphTest)

enable_testing()
add_test(NAME MyGraphTest COMMAND MyGraphTest)

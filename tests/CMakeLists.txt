cmake_minimum_required(VERSION 3.26)
project(MyGraphTest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        MyGraphTest
        graphTest.cpp
        MatrixTest.cpp
        ../src/Matrix.cpp
        ../src/Graph.cpp
)
target_link_libraries(
        MyGraphTest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(MyGraphTest)









## Include the directories where your header files reside
#include_directories(${GTEST_INCLUDE_DIRS})
#
## Add your test source files
#add_executable(MyGraphTest graphTest.cpp ../src/Graph.cpp MatrixTest.cpp ../src/Matrix.cpp)
#
## Link your test target with Google Test and any other libraries
#target_link_libraries(MyGraphTest gtest gtest_main)
#
## Find and configure Google Test
#find_package(GTest REQUIRED)
#
## Register your test
#add_test(NAME MyGraphTest COMMAND MyGraphTest)

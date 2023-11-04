cmake_minimum_required(VERSION 3.26)
project(ggraph)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable(ggraph
    ${SOURCES}
    ${HEADERS}
)

# Include the "tests" directory
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.26)
project(ggraph)

set(CMAKE_CXX_STANDARD 23)

# Include the directories where your header files reside
include_directories(include)

add_executable(ggraph
        src/main.cpp
        src/ListGraph.cpp
)

# Include the "tests" directory
add_subdirectory(tests)

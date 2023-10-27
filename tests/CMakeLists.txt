project(MyGraphTest)

# Include the directories where your header files reside
include_directories(${GTEST_INCLUDE_DIRS})

# Add your test source files
add_executable(MyGraphTest graphTest.cpp ../src/Graph.cpp MatrixTest.cpp ../src/Matrix.cpp)

# Link your test target with Google Test and any other libraries
target_link_libraries(MyGraphTest gtest gtest_main)

# Register your test
add_test(NAME MyGraphTest COMMAND MyGraphTest)

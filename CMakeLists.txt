#Require CMake 3.12 or higher
cmake_minimum_required(VERSION 3.12)
project("GDB-Tech-Test")

option(BUILD_TESTS OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

add_executable(${PROJECT_NAME} src/main.cpp src/Vector2.h src/Solver.h)




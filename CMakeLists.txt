#Require CMake 3.14 or higher
cmake_minimum_required(VERSION 3.14)
project("GDB-Tech-Test")

#Build Tests, if enabled. 
option(BUILD_TESTS OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

#Build the main project. 
add_executable(${PROJECT_NAME} src/main.cpp src/Vector2.h src/Solver.h)




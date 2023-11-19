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

#Copy data files to the binary directory
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#Set the working directory to the project root (for Windows builds only)
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")



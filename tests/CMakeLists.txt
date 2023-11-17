cmake_minimum_required(VERSION 3.12)
project("Tests")

include(FetchContent)

find_package(GTest REQUIRED) #Try to find a current installation of gtest.
if(NOT GTest_FOUND) 
    FetchContent_Declare( #If we couldn't find gtest, download the repo.
        GTest
        GIT_REPOSITORY https://github.com/google/googletest
    )

    FetchContent_MakeAvailable(GTest)
endif()

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} gtest)


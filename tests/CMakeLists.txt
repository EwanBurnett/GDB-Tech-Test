cmake_minimum_required(VERSION 3.14)
project("Tests")

include(FetchContent)

find_package(GTest) #Try to find a current installation of gtest.
if(NOT GTest_FOUND) 
    FetchContent_Declare( #If we couldn't find gtest, download the repo.
        GTest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG "origin/main"
    )

    #Prevent google test from overriding the parent project's compiler / linker settings [WINDOWS]
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(GTest)
endif()

add_executable(${PROJECT_NAME} tests.cpp)
target_link_libraries(${PROJECT_NAME} gtest)
set_target_properties(${PROJECT_NAME} PROPERTIES 
    CXX_STANDARD 14     #Google Test requires C++ 14 or higher.
    CXX_STANDARD_REQUIRED ON
)



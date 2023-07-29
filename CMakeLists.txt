cmake_minimum_required(VERSION 3.0.0)
project(
    dict
    VERSION 0.1.0 
    LANGUAGES C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
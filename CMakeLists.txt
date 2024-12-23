cmake_minimum_required(VERSION 3.30..3.31)
project(OpenSTL LANGUAGES CXX)

add_subdirectory(extern/catch)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
add_library(OpenSTL::OpenSTL ALIAS ${PROJECT_NAME})

include(CTest)
add_subdirectory(tests)

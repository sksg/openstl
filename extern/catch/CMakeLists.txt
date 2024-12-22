cmake_minimum_required(VERSION 3.30..3.31)
project(Catch LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)
add_library(Catch::Catch ALIAS ${PROJECT_NAME})


add_library(${PROJECT_NAME}-with-main INTERFACE)
target_include_directories(${PROJECT_NAME}-with-main INTERFACE include)
target_compile_definitions(${PROJECT_NAME}-with-main INTERFACE "CATCH_CONFIG_MAIN")
add_library(Catch::CatchWithMain ALIAS ${PROJECT_NAME}-with-main)
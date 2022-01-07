cmake_minimum_required(VERSION 3.15)


add_library(${PROJECT_NAME} INTERFACE)  # TODO: Change to proper library and add your files
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

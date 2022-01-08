cmake_minimum_required(VERSION 3.15)

add_subdirectory(units)
add_subdirectory(transformation)

add_library(${PROJECT_NAME}
        context.h
        context.cpp
        )
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC units)

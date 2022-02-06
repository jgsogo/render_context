cmake_minimum_required(VERSION 3.15)

find_package(Magnum REQUIRED Primitives)

add_subdirectory(units)
add_subdirectory(transformation)
add_subdirectory(render)
add_subdirectory(primitives)


add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME}
        INTERFACE
        units
        transformation
        render
        render_imgui
        primitives
        )
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})

install(TARGETS ${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

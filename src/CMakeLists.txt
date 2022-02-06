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

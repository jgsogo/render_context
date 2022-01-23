
add_library(primitives
        primitive.hpp
        line_element.hpp

        line.hpp
        )

target_link_libraries(primitives
        PUBLIC
            render
        )
target_include_directories(primitives PUBLIC "../${CMAKE_CURRENT_LIST_DIR}")

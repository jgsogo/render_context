
add_library(render
        #primitive.hpp

        imgui.h
        imgui.cpp
        context.h
        )

target_link_libraries(render
        PUBLIC
        units
        transformation
        )
target_include_directories(render PUBLIC "../${CMAKE_CURRENT_LIST_DIR}")

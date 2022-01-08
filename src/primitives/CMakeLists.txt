
add_library(primitives
        #primitive.hpp

        render.h
        render.cpp
        )

target_link_libraries(primitives
        PUBLIC
        units
        )
target_include_directories(primitives PUBLIC "../${CMAKE_CURRENT_LIST_DIR}")

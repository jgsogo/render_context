
add_library(primitives INTERFACE)
set_target_properties(primitives PROPERTIES
        LINKER_LANGUAGE CXX
        PUBLIC_HEADER "arc.hpp;base_polygon.hpp;image.hpp;line.hpp;line_element.hpp;polygon.hpp;primitive.hpp;rectangle.hpp;text.hpp"
        )

target_link_libraries(primitives
        INTERFACE
            render
        )
target_include_directories(primitives INTERFACE "${CMAKE_CURRENT_LIST_DIR}/..")

install(TARGETS primitives
        PUBLIC_HEADER DESTINATION include/primitives
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

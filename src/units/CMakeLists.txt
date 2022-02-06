
add_library(units INTERFACE)
set_target_properties(units PROPERTIES
        LINKER_LANGUAGE CXX
        PUBLIC_HEADER "degrees.hpp;milimeters.hpp;named_unit.hpp;pixels.hpp;ratio.hpp"
        )
target_link_libraries(units
        INTERFACE
        Magnum::Primitives
        )
target_include_directories(units INTERFACE "${CMAKE_CURRENT_LIST_DIR}/..")

install(TARGETS units
        PUBLIC_HEADER DESTINATION include/units
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

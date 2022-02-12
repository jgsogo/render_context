
add_library(units
        degrees.hpp
        milimeters.cpp
        milimeters.hpp
        named_unit.hpp
        pixels.hpp
        ratio.hpp
        )
set_target_properties(units PROPERTIES
        PUBLIC_HEADER "degrees.hpp;milimeters.hpp;named_unit.hpp;pixels.hpp;ratio.hpp"
        )
target_link_libraries(units
        PUBLIC
        Magnum::Primitives
        )
target_include_directories(units PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

install(TARGETS units
        PUBLIC_HEADER DESTINATION include/units
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

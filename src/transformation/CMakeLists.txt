
add_library(transformation INTERFACE)
set_target_properties(transformation PROPERTIES
        PUBLIC_HEADER "transformation.hpp"
        )
target_link_libraries(transformation
        INTERFACE
        Magnum::Primitives
        )
target_include_directories(transformation INTERFACE "${CMAKE_CURRENT_LIST_DIR}/..")
install(TARGETS transformation
        PUBLIC_HEADER DESTINATION include/transformation
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


add_library(transformation INTERFACE)
target_link_libraries(transformation
        INTERFACE
        Magnum::Primitives
        )

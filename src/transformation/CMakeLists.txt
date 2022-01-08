
find_package(Magnum REQUIRED Primitives)

add_library(transformation INTERFACE)
target_link_libraries(transformation
        INTERFACE
        Magnum::Primitives
        )

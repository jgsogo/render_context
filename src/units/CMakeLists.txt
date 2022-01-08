
find_package(Magnum REQUIRED Primitives)

add_library(units INTERFACE)
target_link_libraries(units
        INTERFACE
        Magnum::Primitives
        )

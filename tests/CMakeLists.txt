cmake_minimum_required(VERSION 3.15)

find_package(Catch2 REQUIRED)

enable_testing()

add_executable(unit_tests
        main.cpp

        test_units/test_milimeters.cpp
        test_units/test_pixels.cpp
        test_units/test_ratio.cpp
        test_units/test_named_unit.cpp
        test_units/test_operations.cpp

        test_transformation/test_2d_matrix.cpp
        test_transformation/test_operations.cpp
        test_transformation/test_inverted.cpp
        test_transformation/test_utils.cpp

        test_render/test_imgui_context.cpp
        test_render/test_imgui_functions.cpp
        test_render/test_imgui_primitives.cpp
        test_render/test_context.cpp

        test_primitives/test_line.cpp
        test_primitives/test_arc.cpp
        test_primitives/test_polygon.cpp
        test_primitives/test_rectangle.cpp
        test_primitives/test_text.cpp
        test_primitives/test_image.cpp
        )
target_link_libraries(unit_tests
        Catch2::Catch2
        ${PROJECT_NAME}
        )

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(Catch)
catch_discover_tests(unit_tests)

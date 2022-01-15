
find_package(MagnumIntegration REQUIRED ImGui)
find_package(imgui REQUIRED)

add_library(render INTERFACE)

target_link_libraries(render
        INTERFACE
            units
            transformation
            MagnumIntegration::ImGui
            imgui::imgui
        )
target_include_directories(render INTERFACE "../${CMAKE_CURRENT_LIST_DIR}")

# Custom implementations, TODO: include if option
add_subdirectory(imgui)

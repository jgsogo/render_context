
find_package(MagnumIntegration REQUIRED ImGui)
find_package(imgui REQUIRED)

add_library(render INTERFACE)
set_target_properties(render PROPERTIES
        LINKER_LANGUAGE CXX
        PUBLIC_HEADER "context.h"
        )
target_link_libraries(render
        INTERFACE
            units
            transformation
            MagnumIntegration::ImGui
            imgui::imgui
        )
target_include_directories(render INTERFACE "${CMAKE_CURRENT_LIST_DIR}/..")

install(TARGETS render
        PUBLIC_HEADER DESTINATION include/render
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


# Custom implementations, TODO: include if option
add_subdirectory(imgui)

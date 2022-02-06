
find_package(imgui REQUIRED)

add_library(render_imgui INTERFACE)

target_link_libraries(render_imgui
        INTERFACE
        render
        imgui::imgui
        )
target_include_directories(render_imgui INTERFACE "../../${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(render_imgui
        INTERFACE
        IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_LIST_DIR}/imconfig.h\"
        )

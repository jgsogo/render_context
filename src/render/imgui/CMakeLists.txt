
find_package(imgui REQUIRED)

add_library(render_imgui INTERFACE)
set_target_properties(render_imgui PROPERTIES
        LINKER_LANGUAGE CXX
        PUBLIC_HEADER "context.h;imconfig.h;pixels.hpp"
        )
target_link_libraries(render_imgui
        INTERFACE
        render
        imgui::imgui
        )
target_include_directories(render_imgui INTERFACE "${CMAKE_CURRENT_LIST_DIR}/../..")
target_compile_definitions(render_imgui
        INTERFACE
        IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_LIST_DIR}/imconfig.h\"
        )

install(TARGETS render_imgui
        PUBLIC_HEADER DESTINATION include/render/imgui
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


find_package(imgui REQUIRED)

add_library(render_imgui
        context.h
        context.cpp
        imconfig.h
        pixels.hpp
        )
set_target_properties(render_imgui PROPERTIES
        PUBLIC_HEADER "context.h;imconfig.h;pixels.hpp"
        )
target_link_libraries(render_imgui
        PUBLIC
        render
        imgui::imgui
        )
target_include_directories(render_imgui PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../..")
target_compile_definitions(render_imgui
        PUBLIC
        IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_LIST_DIR}/imconfig.h\"
        )

install(TARGETS render_imgui
        PUBLIC_HEADER DESTINATION include/render/imgui
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

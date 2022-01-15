
find_package(imgui REQUIRED)

add_library(render_imgui
        #primitive.hpp
        imconfig.h
        context.h
        context.cpp
        )

target_link_libraries(render_imgui
        PUBLIC
        render
        imgui::imgui
        )
target_include_directories(render_imgui PUBLIC "../../${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(render_imgui
        PUBLIC
        IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_LIST_DIR}/imconfig.h\"
        )



find_package(MagnumIntegration REQUIRED ImGui)
find_package(imgui REQUIRED)

add_library(render
        #primitive.hpp
        imconfig.h
        imgui_functions.h
        imgui_functions.cpp
        context.h
        )

target_link_libraries(render
        PUBLIC
            units
            transformation
            MagnumIntegration::ImGui
            imgui::imgui
        )
target_include_directories(render PUBLIC "../${CMAKE_CURRENT_LIST_DIR}")
target_compile_definitions(render
        PUBLIC
        IMGUI_USER_CONFIG=\"${CMAKE_CURRENT_LIST_DIR}/imconfig.h\"
        )

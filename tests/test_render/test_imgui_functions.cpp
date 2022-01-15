
#include <imgui_internal.h>
#include "catch2/catch.hpp"
#include "units/units.hpp"
#include "render/imgui_functions.h"

using namespace math::units;

/*
 * TODO: Figure out what to test, what value to check... meanwhile, just executing these functions
 * TODO:  is useful to know they just work (and templates are instantiated)
 * */

TEST_CASE("test_render/test_imgui_functions | Draw a circle", "[render/imgui]") {
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(1920, 1080);
    io.DeltaTime = 1.0f / 60.0f;

    // Build atlas
    unsigned char *tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

    ImGui::NewFrame();
    auto drawlist = ImGui::GetWindowDrawList();

    SECTION("Draw circle") {
        render::imgui::Vector2Px center{0_px, 0_px};
        ImU32 color = IM_COL32_BLACK;
        render::imgui::drawCircle(*drawlist, center, 10_px, color, 2_px);
    }

    SECTION("Draw line") {
        render::imgui::Vector2Px start{0_px, 0_px};
        render::imgui::Vector2Px end{0_px, 0_px};
        ImU32 color = IM_COL32_BLACK;
        render::imgui::drawLine(*drawlist, start, end, color, 2_px);
    }

    ImGui::DestroyContext();
    //REQUIRE(os.str() == "[mm > px] scale(1 px/mm), rotate(0), translate(0 px, 0 px)");
}
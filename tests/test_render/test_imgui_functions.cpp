
#include "catch2/catch.hpp"
#include "render/imgui/context.h"


using namespace render::imgui::units;
/*
 * TODO: Figure out what to test, what value to check... meanwhile, just executing these functions
 * TODO:  is useful to know they just work (and templates are instantiated, if any)
 * */

TEST_CASE("test_render/test_imgui_context | Draw functions", "[render/imgui]") {
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
        Magnum::Math::Vector2 center{0_impx, 0_impx};
        render::drawCircle(*drawlist, center, 10_impx, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw line") {
        Magnum::Math::Vector2 start{0_impx, 0_impx};
        Magnum::Math::Vector2 end{0_impx, 0_impx};
        render::drawLine(*drawlist, start, end, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<render::imgui::Pixels> rect;
        rect.topRight() = {100_impx, 0_impx};
        rect.bottomLeft() = {0_impx, 20_impx};
        render::drawRectangle(*drawlist, rect, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw rectangle filled") {
        Magnum::Math::Range2D<render::imgui::Pixels> rect;
        rect.topRight() = {100_impx, 0_impx};
        rect.bottomLeft() = {0_impx, 20_impx};
        render::drawRectangleFilled(*drawlist, rect, IM_COL32_BLACK);
    }

    SECTION("Draw polyline") {
        std::vector<Magnum::Math::Vector2<render::imgui::Pixels>> points;
        points.emplace_back(0_impx, 0_impx);
        points.emplace_back(10_impx, 10_impx);
        render::drawPolyline(*drawlist, points, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw polyline filled") {
        std::vector<Magnum::Math::Vector2<render::imgui::Pixels>> points;
        points.emplace_back(0_impx, 0_impx);
        points.emplace_back(10_impx, 10_impx);
        render::drawPolylineFilled(*drawlist, points, IM_COL32_BLACK);
    }

    SECTION("Draw text") {
        Magnum::Math::Vector2 position{10_impx, 10_impx};
        render::drawText(*drawlist, position, 10.f, IM_COL32_BLACK, "Some text");
    }

    SECTION("Draw image") {
        Magnum::Math::Range2D<render::imgui::Pixels> uvCoords;
        uvCoords.topRight() = {100_impx, 0_impx};
        uvCoords.bottomLeft() = {0_impx, 20_impx};

        std::array<Magnum::Math::Vector2<render::imgui::Pixels>, 4> bbox;
        // TODO: Load texture and call function
    }

    ImGui::DestroyContext();
}

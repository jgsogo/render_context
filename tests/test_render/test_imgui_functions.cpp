
#include "catch2/catch.hpp"
#include "units/units.hpp"
#include "render/imgui/context.h"

using namespace math::units;

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
        render::Vector2Px center{0_px, 0_px};
        render::drawCircle(*drawlist, center, 10_px, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw line") {
        render::Vector2Px start{0_px, 0_px};
        render::Vector2Px end{0_px, 0_px};
        render::drawLine(*drawlist, start, end, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<math::Pixels> rect;
        rect.topRight() = {100_px, 0_px};
        rect.bottomLeft() = {0_px, 20_px};
        render::drawRectangle(*drawlist, rect, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw rectangle filled") {
        Magnum::Math::Range2D<math::Pixels> rect;
        rect.topRight() = {100_px, 0_px};
        rect.bottomLeft() = {0_px, 20_px};
        render::drawRectangleFilled(*drawlist, rect, IM_COL32_BLACK);
    }

    SECTION("Draw polyline") {
        std::vector<render::Vector2Px> points;
        points.emplace_back(0_px, 0_px);
        points.emplace_back(10_px, 10_px);
        render::drawPolyline(*drawlist, points, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw polyline filled") {
        std::vector<render::Vector2Px> points;
        points.emplace_back(0_px, 0_px);
        points.emplace_back(10_px, 10_px);
        render::drawPolylineFilled(*drawlist, points, IM_COL32_BLACK);
    }

    SECTION("Draw text") {
        render::Vector2Px position{10_px, 10_px};
        render::drawText(*drawlist, position, 10.f, IM_COL32_BLACK, "Some text");
    }

    SECTION("Draw image") {
        Magnum::Math::Range2D<math::Pixels> uvCoords;
        uvCoords.topRight() = {100_px, 0_px};
        uvCoords.bottomLeft() = {0_px, 20_px};

        std::array<render::Vector2Px, 4> bbox;
        // TODO: Load texture and call function
        //Magnum::GL::Texture2D textureID;
        //render::imgui::drawImage(*drawlist, textureID, uvCoords, bbox);
    }

    ImGui::DestroyContext();
}

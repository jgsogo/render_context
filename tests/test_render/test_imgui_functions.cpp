
#include "catch2/catch.hpp"
#include "render/imgui/context.h"


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
        Magnum::Math::Vector2<float> center{0.f, 0.f};
        render::drawCircle(*drawlist, center, 10.f, IM_COL32_BLACK, 2.f);
    }

    SECTION("Draw line") {
        Magnum::Math::Vector2<float> start{0.f, 0.f};
        Magnum::Math::Vector2<float> end{0.f, 0.f};
        render::drawLine(*drawlist, start, end, IM_COL32_BLACK, 2.f);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<float> rect;
        rect.topRight() = {100.f, 0.f};
        rect.bottomLeft() = {0.f, 20.f};
        render::drawRectangle(*drawlist, rect, IM_COL32_BLACK, 2.f);
    }

    SECTION("Draw rectangle filled") {
        Magnum::Math::Range2D<float> rect;
        rect.topRight() = {100.f, 0.f};
        rect.bottomLeft() = {0.f, 20.f};
        render::drawRectangleFilled(*drawlist, rect, IM_COL32_BLACK);
    }

    SECTION("Draw polyline") {
        std::vector<Magnum::Math::Vector2<float>> points;
        points.emplace_back(0.f, 0.f);
        points.emplace_back(10.f, 10.f);
        render::drawPolyline(*drawlist, points, IM_COL32_BLACK, 2.f);
    }

    SECTION("Draw polyline filled") {
        std::vector<Magnum::Math::Vector2<float>> points;
        points.emplace_back(0.f, 0.f);
        points.emplace_back(10.f, 10.f);
        render::drawPolylineFilled(*drawlist, points, IM_COL32_BLACK);
    }

    SECTION("Draw text") {
        Magnum::Math::Vector2<float> position{10.f, 10.f};
        render::drawText(*drawlist, position, 10.f, IM_COL32_BLACK, "Some text");
    }

    SECTION("Draw image") {
        Magnum::Math::Range2D<float> uvCoords;
        uvCoords.topRight() = {100.f, 0.f};
        uvCoords.bottomLeft() = {0.f, 20.f};

        std::array<Magnum::Math::Vector2<float>, 4> bbox;
        // TODO: Load texture and call function
    }

    ImGui::DestroyContext();
}

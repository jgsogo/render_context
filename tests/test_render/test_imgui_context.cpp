
#include "catch2/catch.hpp"
#include "units/units.hpp"
#include "render/imgui/context.h"

using namespace math::units;

/*
 * TODO: Figure out what to test, what value to check... meanwhile, just executing these functions
 * TODO:  is useful to know they just work (and templates are instantiated, if any)
 * */
TEST_CASE("test_render/test_imgui_context | Instantiate context", "[render/imgui]") {
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

    render::ImGuiContext<math::types::MilimetersT> context{*drawlist};
    using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

    SECTION("Draw circle") {
        Vector2Mm center{0_mm, 0_mm};
        context.drawCircle(center, 10_mm, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw line") {
        Vector2Mm start{0_mm, 0_mm};
        Vector2Mm end{0_mm, 0_mm};
        context.drawLine(start, end, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<math::Milimeters> rect;
        rect.topRight() = {100_mm, 0_mm};
        rect.bottomLeft() = {0_mm, 20_mm};
        context.drawRectangle(rect, IM_COL32_BLACK, 2_px);
    }

    SECTION("Draw rectangle filled") {
        Magnum::Math::Range2D<math::Milimeters> rect;
        rect.topRight() = {100_mm, 0_mm};
        rect.bottomLeft() = {0_mm, 20_mm};
        context.drawRectangleFilled(rect, IM_COL32_BLACK);
    }

    SECTION("Draw polyline") {
        std::vector<Vector2Mm> points;
        points.emplace_back(0_mm, 0_mm);
        points.emplace_back(10_mm, 10_mm);
        context.drawPolyline(points, IM_COL32_BLACK, 2_px, 0);
    }

    SECTION("Draw polyline filled") {
        std::vector<Vector2Mm> points;
        points.emplace_back(0_mm, 0_mm);
        points.emplace_back(10_mm, 10_mm);
        context.drawPolylineFilled(points, IM_COL32_BLACK);
    }

    SECTION("Draw text") {
        Vector2Mm position{10_mm, 10_mm};
        context.drawText(position, 10.f, IM_COL32_BLACK, "Some text");
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
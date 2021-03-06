
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "render/imgui/context.h"
#include <Magnum/ImGuiIntegration/Context.hpp>

using namespace math::units;
using namespace render::units;
using namespace render::imgui::units;

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

    render::ImGuiContext<math::Milimeters::symbol> context{*drawlist};
    using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

    SECTION("Draw circle") {
        Vector2Mm center{0_mm, 0_mm};
        context.drawCircle(center, 10_mm, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw line") {
        Vector2Mm start{0_mm, 0_mm};
        Vector2Mm end{0_mm, 0_mm};
        context.drawLine(start, end, IM_COL32_BLACK, 2_impx);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<math::Milimeters> rect;
        rect.topRight() = {100_mm, 0_mm};
        rect.bottomLeft() = {0_mm, 20_mm};
        context.drawRectangle(rect, IM_COL32_BLACK, 2_impx);
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
        context.drawPolyline(points, IM_COL32_BLACK, 2_impx, 0);
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
        Magnum::Math::Range2D<render::UVCoordinates> uvCoords;
        uvCoords.topRight() = {100_uv, 0_uv};
        uvCoords.bottomLeft() = {0_uv, 20_uv};

        Magnum::Math::Range2D<math::Milimeters> bbox;
        Magnum::GL::Texture2D textureID{Magnum::NoCreate};

        context.drawImage(textureID, uvCoords, bbox);
    }

    ImGui::DestroyContext();
}

TEST_CASE("test_render/test_imgui_context | Concatenate contexts", "[render/imgui]") {
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

    render::ImGuiContext<math::Milimeters::symbol> context{*drawlist};

    SECTION("Apply transformation and draw") {
        math::xy::types::Transformation<math::units::px, math::units::mm, float> t;
        auto ctxt = context << t;
        Magnum::Math::Vector2<math::types::PixelsT<float>> center{0_px, 0_px};
        ctxt.drawCircle(center, 10_px, IM_COL32_BLACK, 2_impx);
    }

    ImGui::DestroyContext();

}
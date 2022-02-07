
#include <catch2/catch.hpp>
#include <Magnum/ImGuiIntegration/Context.hpp>
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "render/imgui/context.h"
#include "primitives/arc.hpp"
#include "primitives/image.hpp"
#include "primitives/line.hpp"
#include "primitives/polygon.hpp"
#include "primitives/rectangle.hpp"
#include "primitives/text.hpp"

using namespace math::units;
using namespace render::units;
using namespace render::imgui::units;

/*
 * TODO: Figure out what to test, what value to check... meanwhile, just executing these functions
 * TODO:  is useful to know they just work (and templates are instantiated, if any)
 * */
TEST_CASE("test_render/test_imgui_primitives | Instantiate context", "[render/imgui]") {
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

    render::ImGuiContext<math::units::mm> context{*drawlist};
    using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

    SECTION("Draw arc") {
        auto arc = primitives::Arc<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{};
        arc.color = IM_COL32_BLACK;
        arc.thickness = 23_impx;
        arc.center = {0_mm, 0_mm};
        arc.radius = 20_mm;
        arc.start = 10_deg;
        arc.end = 20_deg;
        arc.doRender(context);
    }

    SECTION("Draw image") {
        Magnum::GL::Texture2D textureID{Magnum::NoCreate};
        auto image = primitives::Image<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{textureID};
        image.texture.uvCoordinates.topRight() = {0_uv, 0_uv};
        image.texture.uvCoordinates.bottomLeft() = {10_uv, 10_uv};
        image.bbox.topRight() = {0_mm, 0_mm};
        image.bbox.bottomLeft() = {0_mm, 0_mm};
        image.doRender(context);
    }

    SECTION("Draw line") {
        auto line = primitives::Line<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{};
        line.color = IM_COL32_BLACK;
        line.thickness = 23_impx;
        line.start = {0_mm, 0_mm};
        line.end = {10_mm, 0_mm};
        line.doRender(context);
    }

    SECTION("Draw polygon") {
        auto poly = primitives::ConvexPolygon<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{};
        poly.filled = true;
        poly.fillColor = IM_COL32_BLACK;
        poly.border = true;
        poly.borderColor = IM_COL32(255, 0, 0, 255);
        poly.borderThickness = 23_impx;
        {
            auto line1 = std::make_shared<primitives::Line<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>>();
            line1->color = IM_COL32_BLACK;
            line1->thickness = 23_impx;
            line1->start = {0_mm, 0_mm};
            line1->end = {10_mm, 0_mm};
            poly.lineElements.push_back(line1);

            auto line2 = std::make_shared<primitives::Line<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>>();
            line2->color = IM_COL32_BLACK;
            line2->thickness = 23_impx;
            line2->start = {10_mm, 0_mm};
            line2->end = {0_mm, 10_mm};
            poly.lineElements.push_back(line2);
        }
        poly.doRender(context);
    }

    SECTION("Draw rectangle") {
        auto poly = primitives::Rectangle<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{};
        poly.filled = true;
        poly.fillColor = IM_COL32_BLACK;
        poly.border = true;
        poly.borderColor = IM_COL32(255, 0, 0, 255);
        poly.borderThickness = 23_impx;
        poly.rect = Magnum::Math::Range2D<math::Milimeters>{
                {0_mm,  0_mm},
                {20_mm, 10_mm}
        };
        poly.doRender(context);
    }

    SECTION("Draw text") {
        auto txt = primitives::Text<math::Milimeters::symbol, ImDrawList, render::imgui::units::impx>{};
        txt.color = IM_COL32_BLACK;
        txt.fontSize = 23.f;
        txt.position.set({10_mm, 20_mm});
        txt.position.set(45_deg);
        txt.content = "content";
        txt.doRender(context);
    }

    ImGui::DestroyContext();
}

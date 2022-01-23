
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/arc.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;

TEST_CASE("test_primitives/test_arc | Draw a arc", "[render/mock]") {
    auto arc = primitives::Arc<math::Milimeters::symbol, mocks::DrawList>{};
    arc.color = IM_COL32_BLACK;
    arc.thickness = 23_px;
    arc.center = {0_mm, 0_mm};
    arc.radius = 20_mm;
    arc.start = 10_deg;
    arc.end = 20_deg;

    primitives::Primitive<math::Milimeters::symbol, mocks::DrawList> &primitive = arc;
    SECTION("Draw") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawLine.size() == 1);
        REQUIRE(std::get<0>(drwList.drawLine[0]) == render::Vector2Px{0_px, 0_px});
        REQUIRE(std::get<1>(drwList.drawLine[0]) == render::Vector2Px{10_px, 0_px});
        REQUIRE(std::get<2>(drwList.drawLine[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawLine[0]) == 23_px);
    }

    SECTION("Polyline") {
        primitives::LineElement<math::Milimeters::symbol, mocks::DrawList> &lineElement = arc;
        auto polyline = lineElement.getPolyline();
        REQUIRE(polyline.size() == 2);
        //REQUIRE(polyline.at(0) == line.start);
        //REQUIRE(polyline.at(1) == line.end);
    }
}

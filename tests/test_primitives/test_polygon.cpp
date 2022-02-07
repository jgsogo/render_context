
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/polygon.hpp"
#include "primitives/line.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;

TEST_CASE("test_primitives/test_polygon | Draw a polygon", "[render/mock]") {
    auto poly = primitives::ConvexPolygon<math::Milimeters::symbol, mocks::DrawList, math::units::px>{};
    poly.filled = true;
    poly.fillColor = IM_COL32_BLACK;
    poly.border = true;
    poly.borderColor = IM_COL32(255, 0, 0, 255);
    poly.borderThickness = 23_px;
    {
        auto line1 = std::make_shared<primitives::Line<math::Milimeters::symbol, mocks::DrawList, math::units::px>>();
        line1->color = IM_COL32_BLACK;
        line1->thickness = 23_px;
        line1->start = {0_mm, 0_mm};
        line1->end = {10_mm, 0_mm};
        poly.lineElements.push_back(line1);

        auto line2 = std::make_shared<primitives::Line<math::Milimeters::symbol, mocks::DrawList, math::units::px>>();
        line2->color = IM_COL32_BLACK;
        line2->thickness = 23_px;
        line2->start = {10_mm, 0_mm};
        line2->end = {0_mm, 10_mm};
        poly.lineElements.push_back(line2);
    }

    primitives::Primitive<math::Milimeters::symbol, mocks::DrawList, math::units::px> &primitive = poly;
    SECTION("Draw filled") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList, math::units::px>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawPolylineFilled.size() == 1);

        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).size() == 4);
        REQUIRE(std::get<1>(drwList.drawPolylineFilled[0]) == IM_COL32_BLACK);
    }

    SECTION("Draw not filled") {
        poly.filled = false;
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList, math::units::px>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawLine.empty());
        REQUIRE(drwList.drawPolyline.size() == 1);

        REQUIRE(std::get<0>(drwList.drawPolyline[0]).size() == 4);
        REQUIRE(std::get<1>(drwList.drawPolyline[0]) == IM_COL32(255, 0, 0, 255));
        REQUIRE(std::get<2>(drwList.drawPolyline[0]) == 23_px);
        REQUIRE(std::get<3>(drwList.drawPolyline[0]) == ImDrawFlags_Closed);
    }

}


#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/rectangle.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;

TEST_CASE("test_primitives/test_rectangle | Draw a rectangle", "[render/mock]") {
    auto poly = primitives::Rectangle<math::Milimeters::symbol, mocks::DrawList>{};
    poly.filled = true;
    poly.fillColor = IM_COL32_BLACK;
    poly.border = true;
    poly.borderColor = IM_COL32(255, 0, 0, 255);
    poly.borderThickness = 23_px;
    poly.rect = Magnum::Math::Range2D<math::Milimeters>{
            {0_mm,  0_mm},
            {20_mm, 10_mm}
    };

    primitives::Primitive<math::Milimeters::symbol, mocks::DrawList> &primitive = poly;
    SECTION("Draw filled") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawPolylineFilled.size() == 1);

        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).size() == 4);
        REQUIRE(std::get<1>(drwList.drawPolylineFilled[0]) == IM_COL32_BLACK);
    }

    SECTION("Draw not filled") {
        poly.filled = false;
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawLine.empty());
        REQUIRE(drwList.drawPolyline.size() == 1);

        REQUIRE(std::get<0>(drwList.drawPolyline[0]).size() == 4);
        REQUIRE(std::get<1>(drwList.drawPolyline[0]) == IM_COL32(255, 0, 0, 255));
        REQUIRE(std::get<2>(drwList.drawPolyline[0]) == 23.f);
        REQUIRE(std::get<3>(drwList.drawPolyline[0]) == ImDrawFlags_Closed);
    }

}

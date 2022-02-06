
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/line.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;
using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

TEST_CASE("test_primitives/test_line | Draw a line", "[render/mock]") {
    auto line = primitives::Line<math::Milimeters::symbol, mocks::DrawList>{};
    line.color = IM_COL32_BLACK;
    line.thickness = 23_px;
    line.start = {0_mm, 0_mm};
    line.end = {10_mm, 0_mm};

    primitives::Primitive<math::Milimeters::symbol, mocks::DrawList> &primitive = line;
    SECTION("Draw") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawLine.size() == 1);
        REQUIRE(std::get<0>(drwList.drawLine[0]) == Magnum::Math::Vector2{0.f, 0.f});
        REQUIRE(std::get<1>(drwList.drawLine[0]) == Magnum::Math::Vector2{10.f, 0.f});
        REQUIRE(std::get<2>(drwList.drawLine[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawLine[0]) == 23.f);
    }

    SECTION("Polyline") {
        primitives::LineElement<math::Milimeters::symbol, mocks::DrawList> &lineElement = line;
        auto polyline = lineElement.getPolyline();
        REQUIRE(polyline.size() == 2);
        REQUIRE(polyline.at(0) == line.start);
        REQUIRE(polyline.at(1) == line.end);
    }
}


#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/degrees.hpp"
#include "primitives/text.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;

TEST_CASE("test_primitives/test_text | Draw text", "[render/mock]") {
    auto txt = primitives::Text<math::Milimeters::symbol, mocks::DrawList>{};
    txt.color = IM_COL32_BLACK;
    txt.fontSize = 23.f;
    txt.position.set({10_mm, 20_mm});
    txt.position.set(45_deg);
    txt.content = "content";

    primitives::Primitive<math::Milimeters::symbol, mocks::DrawList> &primitive = txt;
    SECTION("Draw") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        primitive.doRender(context);
        REQUIRE(drwList.drawLine.empty());
        REQUIRE(drwList.drawText.size() == 1);

        REQUIRE(std::get<0>(drwList.drawText[0]) == Magnum::Math::Vector2{10.f, 20.f});
        REQUIRE(std::get<1>(drwList.drawText[0]) == 23.f);
        REQUIRE(std::get<2>(drwList.drawText[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawText[0]) == "content");
    }

}


#include "catch2/catch.hpp"
#include "units/units.hpp"
#include "render/context.h"

#include "mock_draw_list.hpp"

using namespace math::units;
using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

TEST_CASE("test_render/test_context | Draw functions", "[render/imgui]") {
    mocks::DrawList drwList;
    render::Context<math::types::MilimetersT, mocks::DrawList> ctxtMM{drwList};

    /*
    SECTION("Draw circle") {
        render::imgui::Vector2Px center{0_px, 0_px};
        render::imgui::drawCircle(*drawlist, center, 10_px, IM_COL32_BLACK, 2_px);
    }
     */

    /*
    SECTION("Draw line") {
        Vector2Mm start{0_mm, 00_mm};
        Vector2Mm end{20_mm, 10_mm};
        ctxtMM.drawLine(start, end, IM_COL32_BLACK, 2_px);
    }
     */
}

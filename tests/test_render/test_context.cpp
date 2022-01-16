
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/degrees.hpp"
#include "render/context.h"

#include "mock_draw_list.hpp"

using namespace math::units;
using Vector2Mm = Magnum::Math::Vector2<math::types::MilimetersT<float>>;

TEST_CASE("test_render/test_context | Draw functions", "[render/imgui]") {
    mocks::DrawList drwList;

    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, float>;
    TransformationType::Translation translation{10_mm, 20_mm};
    TransformationType::Rotation rotation{0_deg};
    auto m = TransformationType{translation, rotation};

    auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList} << m;

    SECTION("Draw circle") {
        Vector2Mm center{0_mm, 0_mm};
        context.drawCircle(center, 10_mm, IM_COL32_BLACK, 2_px);
        REQUIRE(drwList.drawCircle.size() == 1);
        REQUIRE(std::get<0>(drwList.drawCircle[0]) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<1>(drwList.drawCircle[0]) == 10_px);
        REQUIRE(std::get<2>(drwList.drawCircle[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawCircle[0]) == 2_px);
    }

    SECTION("Draw line") {
        Vector2Mm start{0_mm, 0_mm};
        Vector2Mm end{10_mm, 10_mm};
        context.drawLine(start, end, IM_COL32_BLACK, 2_px);
        REQUIRE(drwList.drawLine.size() == 1);
        REQUIRE(std::get<0>(drwList.drawLine[0]) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<1>(drwList.drawLine[0]) == render::Vector2Px{20_px, 30_px});
        REQUIRE(std::get<2>(drwList.drawLine[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawLine[0]) == 2_px);
    }

    SECTION("Draw rectangle") {
        Magnum::Math::Range2D<math::Milimeters> rect;
        rect.topRight() = {100_mm, 0_mm};
        rect.bottomLeft() = {0_mm, 20_mm};
        context.drawRectangle(rect, IM_COL32_BLACK, 2_px);

        REQUIRE(drwList.drawRectangle.size() == 0);
        REQUIRE(drwList.drawPolyline.size() == 1);
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).size() == 4);
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(0) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(1) == render::Vector2Px{110_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(2) == render::Vector2Px{110_px, 40_px});
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(3) == render::Vector2Px{10_px, 40_px});
        REQUIRE(std::get<1>(drwList.drawPolyline[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<2>(drwList.drawPolyline[0]) == 2_px);
        REQUIRE(std::get<3>(drwList.drawPolyline[0]) == ImDrawFlags_Closed);
    }

    SECTION("Draw rectangle filled") {
        Magnum::Math::Range2D<math::Milimeters> rect;
        rect.topRight() = {100_mm, 0_mm};
        rect.bottomLeft() = {0_mm, 20_mm};
        context.drawRectangleFilled(rect, IM_COL32_BLACK);

        REQUIRE(drwList.drawRectangleFilled.size() == 0);
        REQUIRE(drwList.drawPolylineFilled.size() == 1);
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).size() == 4);
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(0) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(1) == render::Vector2Px{110_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(2) == render::Vector2Px{110_px, 40_px});
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(3) == render::Vector2Px{10_px, 40_px});
        REQUIRE(std::get<1>(drwList.drawPolylineFilled[0]) == IM_COL32_BLACK);
    }

    SECTION("Draw polyline") {
        std::vector<Vector2Mm> points;
        points.emplace_back(0_mm, 0_mm);
        points.emplace_back(10_mm, 10_mm);
        context.drawPolyline(points, IM_COL32_BLACK, 2_px, 0);

        REQUIRE(drwList.drawPolyline.size() == 1);
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).size() == 2);
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(0) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolyline[0]).at(1) == render::Vector2Px{20_px, 30_px});
        REQUIRE(std::get<1>(drwList.drawPolyline[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<2>(drwList.drawPolyline[0]) == 2_px);
        REQUIRE(std::get<3>(drwList.drawPolyline[0]) == 0);
    }

    SECTION("Draw polyline filled") {
        std::vector<Vector2Mm> points;
        points.emplace_back(0_mm, 0_mm);
        points.emplace_back(10_mm, 10_mm);
        context.drawPolylineFilled(points, IM_COL32_BLACK);

        REQUIRE(drwList.drawPolylineFilled.size() == 1);
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).size() == 2);
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(0) == render::Vector2Px{10_px, 20_px});
        REQUIRE(std::get<0>(drwList.drawPolylineFilled[0]).at(1) == render::Vector2Px{20_px, 30_px});
        REQUIRE(std::get<1>(drwList.drawPolylineFilled[0]) == IM_COL32_BLACK);
    }

    SECTION("Draw text") {
        Vector2Mm position{10_mm, 10_mm};
        context.drawText(position, 10.f, IM_COL32_BLACK, "Some text");

        REQUIRE(drwList.drawText.size() == 1);
        REQUIRE(std::get<0>(drwList.drawText[0]) == render::Vector2Px{20_px, 30_px});
        REQUIRE(std::get<1>(drwList.drawText[0]) == 10.f);
        REQUIRE(std::get<2>(drwList.drawText[0]) == IM_COL32_BLACK);
        REQUIRE(std::get<3>(drwList.drawText[0]) == "Some text");
    }

    SECTION("Draw image") {
        Magnum::Math::Range2D<math::Pixels> uvCoords;
        uvCoords.topRight() = {100_px, 0_px};
        uvCoords.bottomLeft() = {0_px, 20_px};

        std::array<render::Vector2Px, 4> bbox;
        // TODO: Load texture and call function
        //Magnum::GL::Texture2D textureID;
        //render::imgui::drawImage(*drawlist, textureID, uvCoords, bbox);

        // TODO: Implement some checks
    }
}

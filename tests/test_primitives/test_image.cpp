
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/image.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;
using namespace render::units;

TEST_CASE("test_primitives/test_image | Draw image", "[render/mock]") {
    Magnum::GL::Texture2D textureID{Magnum::NoCreate};
    auto image = primitives::Image<math::Milimeters::symbol, mocks::DrawList>{textureID};
    image.texture.uvCoordinates.topRight() = {0_uv, 0_uv};
    image.texture.uvCoordinates.bottomLeft() = {10_uv, 10_uv};
    image.bbox.topRight() = {0_mm, 0_mm};
    image.bbox.bottomLeft() = {0_mm, 0_mm};

    SECTION("Draw") {
        mocks::DrawList drwList;
        auto context = render::Context<math::Milimeters::symbol, mocks::DrawList>{drwList};

        image.doRender(context);
        REQUIRE(drwList.drawImage.size() == 1);

        REQUIRE(std::get<1>(drwList.drawImage[0]) == image.texture.uvCoordinates);
        REQUIRE(std::get<2>(drwList.drawImage[0]) == std::array<render::Vector2Px, 4>{
                render::Vector2Px{0_px, 0_px},
                render::Vector2Px{0_px, 0_px},
                render::Vector2Px{0_px, 0_px},
                render::Vector2Px{0_px, 0_px}
        });
    }

}

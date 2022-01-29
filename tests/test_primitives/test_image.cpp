
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "primitives/image.hpp"

#include "../test_render/mock_draw_list.hpp"

using namespace math::units;

TEST_CASE("test_primitives/test_image | Draw image", "[render/mock]") {
    Magnum::GL::Texture2D textureID{Magnum::NoCreate};
    auto image = primitives::Image<math::Milimeters::symbol, mocks::DrawList>{textureID};
    image.texture.uvCoordinates.topRight() = {render::UVCoordinates{0.f}, render::UVCoordinates{0.f}};
    image.texture.uvCoordinates.bottomLeft() = {render::UVCoordinates{10.f}, render::UVCoordinates{10.f}};;
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

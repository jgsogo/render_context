#include <sstream>
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/degrees.hpp"
#include "transformation/utils.hpp"

using namespace math::units;


TEST_CASE("test_transformation/test_utils | Rotation with center", "[transformation/2d]") {
    auto center = Magnum::Math::Vector2{10_mm, 0_mm};
    auto tf = math::xy::types::rotationWithCenter<math::Milimeters::symbol, float>(30_deg, center);

    std::ostringstream os;
    os << tf;
    REQUIRE(os.str() == "[mm > mm] rotate(30), translate(1.33975 mm, -5 mm)");
    REQUIRE(tf.transformPoint(center) == center);  // Center stays at the same point
    REQUIRE(tf.transformPoint({11_mm, 0_mm}) == Magnum::Math::Vector2{10.866_mm, 0.5_mm});
}

TEST_CASE("test_transformation/test_utils | Scale with center", "[transformation/2d]") {
    auto center = Magnum::Math::Vector2{5_mm, 0_mm};
    auto ratio = math::ratio(1_mm, 10_px);
    auto tf = math::xy::types::scaleWithCenter<math::Milimeters::symbol, math::Pixels::symbol, float>(ratio, center);

    std::ostringstream os;
    os << tf;
    REQUIRE(os.str() == "[mm > px] scale(10 px/mm), rotate(0), translate(-45 px, 0 px)");
    REQUIRE(tf.transformPoint(center) == Magnum::Math::Vector2{5_px, 0_px});  // Center stays at the same point
    REQUIRE(tf.transformPoint({-1_mm, -1_mm}) == Magnum::Math::Vector2{-55_px, -10_px});
}

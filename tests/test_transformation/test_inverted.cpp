#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/degrees.hpp"
#include "transformation/transformation.hpp"

using namespace math::units;

TEST_CASE("test_transformation/test_inverted | Invert without scale", "[transformation/2d/operations]") {
    using Transformation = math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, float>;

    Transformation::Translation translation1{10_mm, 0_mm};
    Transformation::Rotation rotation1{90.0_deg};
    auto t1 = Transformation{translation1, rotation1};

    auto pOri = Magnum::Math::Vector2{10_mm, 20_mm};
    auto pTarget = t1.transformPoint(pOri);

    auto computedOri = t1.transformInverse(pTarget);
    REQUIRE(pOri.x() == computedOri.x());
    REQUIRE(pOri.y() == computedOri.y());
}

TEST_CASE("test_transformation/test_operations | Invert with scale", "[transformation/2d/operations]") {
    using Transformation1 = math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, float>;

    Transformation1::Translation translation1{10_px, 0_px};
    Transformation1::Scale scale1 = math::ratio(1_mm, 2_px);
    Transformation1::Rotation rotation1{90.0_deg};
    auto t1 = Transformation1{translation1, scale1, rotation1};

    auto pOri = Magnum::Math::Vector2{10_mm, 20_mm};
    auto pTarget = t1.transformPoint(pOri);

    auto computedOri = t1.transformInverse(pTarget);
    REQUIRE(pOri.x() == computedOri.x());
    REQUIRE(pOri.y() == computedOri.y());
}

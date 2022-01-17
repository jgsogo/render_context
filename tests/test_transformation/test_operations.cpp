#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/degrees.hpp"
#include "transformation/transformation.hpp"

using namespace math::units;

TEST_CASE("test_transformation/test_operations | Compose operations", "[transformation/2d/operations]") {
    using Transformation = math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, float>;

    Transformation::Translation translation1{10_mm, 0_mm};
    //Transformation::Scale scale1 = math::ratio(1_mm, 1_px);
    Transformation::Rotation rotation1{90.0_deg};
    auto t1 = Transformation{translation1, rotation1};

    Transformation::Translation translation2{100_mm, 0_mm};
    //Transformation::Scale scale2 = math::ratio(8_mm, 1_px);
    Transformation::Rotation rotation2{0.0_deg};
    auto t2 = Transformation{translation2, rotation2};

    SECTION("Transformation t1 * t2") {
        auto t = t1 * t2;
        auto pxs = t.transformPoint({1_mm, 0_mm});
        REQUIRE(pxs.x() == 10_mm);
        REQUIRE(pxs.y() == 101_mm);
    }

    SECTION("Transformation t2 * t1") {
        auto t = t2 * t1;
        auto pxs = t.transformPoint({1_mm, 0_mm});
        REQUIRE(pxs.x() == 110_mm);
        REQUIRE(pxs.y() == 1_mm);
    }
}

TEST_CASE("test_transformation/test_operations | Compose operations with scale", "[transformation/2d/operations]") {
    using Transformation1 = math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, float>;
    using Transformation2 = math::xy::types::Transformation<math::Pixels::symbol, math::Milimeters::symbol, float>;

    Transformation1::Translation translation1{10_px, 0_px};
    Transformation1::Scale scale1 = math::ratio(1_mm, 2_px);
    Transformation1::Rotation rotation1{90.0_deg};
    auto t1 = Transformation1{translation1, scale1, rotation1};

    Transformation2::Translation translation2{100_mm, 0_mm};
    Transformation2::Scale scale2 = math::ratio(2_px, 1_mm);
    Transformation2::Rotation rotation2{0.0_deg};
    auto t2 = Transformation2{translation2, scale2, rotation2};

    SECTION("Transformation t1 * t2") {
        auto t = t1 * t2;
        auto pxs = t.transformPoint({10_px, 0_px});
        REQUIRE(pxs.x() == 10_px);
        REQUIRE(pxs.y() == 210_px);
    }

    SECTION("Transformation t2 * t1") {
        auto t = t2 * t1;
        auto pxs = t.transformPoint({10_mm, 0_mm});
        REQUIRE(pxs.x() == 105_mm);
        REQUIRE(pxs.y() == 10_mm);
    }
}

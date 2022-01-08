#include <sstream>
#include "catch2/catch.hpp"
#include "units/units.hpp"
#include "matrixes/transformation.hpp"

using namespace math::units;


TEST_CASE("test_transformation/test_2d_matrix | Different unit types", "[transformation/2d]") {
    math::xy::types::Transformation<math::types::MilimetersT, math::types::PixelsT, double> m;

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > px] scale(1 px/mm), rotate(0), translate(0 px, 0 px)");
}

TEST_CASE("test_transformation/test_2d_matrix | Same unit type", "[transformation/2d]") {
    math::xy::types::Transformation<math::types::MilimetersT, math::types::MilimetersT, double> m;

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > mm] rotate(0), translate(0 mm, 0 mm)");
}

TEST_CASE("test_transformation/test_2d_matrix | Apply transformation with scale", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::types::MilimetersT, math::types::PixelsT, double>;
    TransformationType::Translation translation{10_px, 20_px};
    TransformationType::Scale scale = math::ratio(8_mm, 1_px);
    TransformationType::Rotation rotation{90.0_deg};

    auto m = TransformationType{translation, scale, rotation};
    {
        std::ostringstream os;
        os << m;
        REQUIRE(os.str() == "[mm > px] scale(0.125 px/mm), rotate(90), translate(10 px, 20 px)");
    }
    auto pxs = m.transformPoint({1_mm, 0_mm});
    REQUIRE(pxs.x() == 10_px);
    REQUIRE(pxs.y() == 20.125_px);
}

TEST_CASE("test_transformation/test_2d_matrix | Apply transformation without scale", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::types::MilimetersT, math::types::MilimetersT, double>;
    TransformationType::Translation translation{10_mm, 20_mm};
    TransformationType::Rotation rotation{90.0_deg};

    auto m = TransformationType{translation, rotation};
    {
        std::ostringstream os;
        os << m;
        REQUIRE(os.str() == "[mm > mm] rotate(90), translate(10 mm, 20 mm)");
    }
    auto tt = m.transformPoint({1_mm, 0_mm});
    REQUIRE(tt.x() == 10_mm);
    REQUIRE(tt.y() == 21_mm);
}

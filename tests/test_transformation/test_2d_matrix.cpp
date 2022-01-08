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

/*
TEST_CASE("test_transformation/test_2d_matrix | Apply transformation with scale", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::types::MilimetersT, math::types::PixelsT, double>;
    TransformationType::Scale ratio = math::ratio(1_mm, 1_px);
    auto m = TransformationType{
            TransformationType::Translation {10_px, 10_px}, ratio, TransformationType::Rotation{90.0_deg}
    };

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > px] scale(1 px/mm), rotate(0), translate(0 px, 0 px)");
}
 */
/*
TEST_CASE("test_transformation/test_2d_matrix | Apply transformation without scale", "[transformation/2d]") {
    math::xy::types::Transformation<math::types::MilimetersT, math::types::PixelsT, double> m;

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > px] scale(1 px/mm), rotate(0), translate(0 px, 0 px)");
}
*/

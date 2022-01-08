#include <sstream>
#include "catch2/catch.hpp"
#include "units/pixels.hpp"
#include "units/milimeters.hpp"
#include "units/ratio.hpp"
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

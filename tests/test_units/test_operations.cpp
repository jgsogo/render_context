
#include <sstream>
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"

using namespace math::units;

/*
 * Units in this project should be able to perform some basics operations to work with other
 * structures and template classses
 * */

TEST_CASE("test_units/test_operations | Assignments from return type", "[units/milimeters]") {
    math::types::MilimetersT<float> result = 10_mm - 23_mm;
    REQUIRE(result == -13_mm);
}


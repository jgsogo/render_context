
#include <sstream>
#include "catch2/catch.hpp"
#include "units/units.hpp"

using namespace math::units;

TEST_CASE("test_units/test_milimeters | Test constructor and literals (unsigned long long)", "[units/milimeters]") {
    math::types::MilimetersT<double> mm1{3000};
    REQUIRE(mm1 == 3000_mm);
    REQUIRE(mm1 == 300_cm);
    REQUIRE(mm1 == 3_m);
}

TEST_CASE("test_units/test_milimeters | Test constructor and literals (long double)", "[units/milimeters]") {
    math::types::MilimetersT<double> mm1{0.3};
    REQUIRE(mm1 == 0.3_mm);
    REQUIRE(mm1 == 0.03_cm);
    REQUIRE(mm1 == 0.0003_m);
}

TEST_CASE("test_units/test_milimeters | Test copy constructor", "[units/milimeters]") {
    math::types::MilimetersT<double> mm1{0.3};
    auto other = mm1;
    REQUIRE(mm1 == other);
}

TEST_CASE("test_units/test_milimeters | Test output stream", "[units/milimeters]") {
    math::types::MilimetersT<double> mm1{0.3};
    std::ostringstream os; os << mm1;
    REQUIRE(os.str() == "0.3 mm");
}

TEST_CASE("test_units/test_milimeters | Test operators", "[units/milimeters]") {
    math::Milimeters mm{3.5f};

    REQUIRE(mm * 2 == 7_mm);
    REQUIRE(2 * mm == 7_mm);

    REQUIRE(mm + 2_mm == 5.5_mm);
    REQUIRE(2_mm + mm == 5.5_mm);

    REQUIRE(mm / 2 == 1.75_mm);
    REQUIRE(3_mm / 1.5 == 2_mm);
}


#include <sstream>
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/named_unit.hpp"

using namespace math::units;

namespace myunits {
    static const char unitSymbol[] = "usymbol";
    using Unit1 = math::types::NamedUnitT<float, unitSymbol>;
}

TEST_CASE("test_units/test_named_unit | Test constructor and literals (unsigned long long)", "[units/named_unit]") {
    myunits::Unit1 u1{300};
    std::ostringstream os;
    os << u1;
    REQUIRE(os.str() == "300 usymbol");
}

TEST_CASE("test_units/test_named_unit | Test constructor and literals (long double)", "[units/named_unit]") {
    math::types::MilimetersT<float> mm1{0.3};
    REQUIRE(mm1 == 0.3_mm);
    REQUIRE(mm1 == 0.03_cm);
    REQUIRE(mm1 == 0.0003_m);
}

TEST_CASE("test_units/test_named_unit | Test copy constructor", "[units/named_unit]") {
    math::types::MilimetersT<float> mm1{0.3};
    auto other = mm1;
    REQUIRE(mm1 == other);
}

TEST_CASE("test_units/test_named_unit | Test output stream", "[units/named_unit]") {
    math::types::MilimetersT<float> mm1{0.3};
    std::ostringstream os; os << mm1;
    REQUIRE(os.str() == "0.3 mm");
}

TEST_CASE("test_units/test_named_unit | Test operators", "[units/named_unit]") {
    math::Milimeters mm{3.5f};

    REQUIRE(mm * 2 == 7_mm);
    REQUIRE(2 * mm == 7_mm);

    REQUIRE(mm + 2_mm == 5.5_mm);
    REQUIRE(2_mm + mm == 5.5_mm);

    REQUIRE(mm / 2 == 1.75_mm);
    REQUIRE(3_mm / 1.5 == 2_mm);
}

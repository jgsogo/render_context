#include <sstream>
#include "catch2/catch.hpp"
#include "units/pixels.hpp"

using namespace math::units;

TEST_CASE("test_units/test_pixels | Test constructor and literals (unsigned long long)", "[units/pixels]") {
    math::types::PixelsT<float> pixels{3000};
    REQUIRE(pixels == 3000_px);
}

TEST_CASE("test_units/test_pixels | Test constructor and literals (long double)", "[units/pixels]") {
    math::types::PixelsT<float> pixels{0.3};
    REQUIRE(pixels == 0.3_px);
}

TEST_CASE("test_units/test_pixels | Test copy constructor", "[units/pixels]") {
    math::types::PixelsT<float> mm1{0.3};
    auto other = mm1;
    REQUIRE(mm1 == other);
}

TEST_CASE("test_units/test_pixels | Test output stream", "[units/pixels]") {
    math::types::PixelsT<float> mm1{0.3};
    std::ostringstream os;
    os << mm1;
    REQUIRE(os.str() == "0.3 px");
}

TEST_CASE("test_units/test_pixels | Test operators", "[units/pixels]") {
    math::Pixels pixels{3.5f};

    REQUIRE(pixels * 2 == 7_px);
    REQUIRE(2 * pixels == 7_px);

    REQUIRE(pixels + 2_px == 5.5_px);
    REQUIRE(2_px + pixels == 5.5_px);

    REQUIRE(pixels / 2 == 1.75_px);
    REQUIRE(3_px / 1.5 == 2_px);
}

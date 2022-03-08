#include <sstream>
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/ratio.hpp"

using namespace math::units;

TEST_CASE("test_units/test_ratio | Ratio and print", "[units/ratio]") {
    auto ratio = math::types::RatioT(1_px, 10_mm);
    std::ostringstream os;
    os << ratio;
    REQUIRE(os.str() == "10 mm/px");
}

TEST_CASE("test_units/test_ratio | Ratio inverse", "[units/ratio]") {
    auto ratio = math::types::RatioT(1_px, 10_mm);
    std::ostringstream os;
    os << ratio.inverse();
    REQUIRE(os.str() == "0.1 px/mm");
}

TEST_CASE("test_units/test_ratio | Inverse ratio", "[units/ratio]") {
    using ForwardRatio = math::types::RatioT<math::Pixels::symbol, math::Milimeters::symbol, float>;
    using BackwardRatio = math::types::RatioT<math::Milimeters::symbol, math::Pixels::symbol, float>;
    auto ratio = ForwardRatio{1_px, 10_mm};
    {
        std::ostringstream os;
        os << ratio;
        REQUIRE(os.str() == "10 mm/px");
    }
    {
        auto inverted = static_cast<BackwardRatio >(ratio);
        std::ostringstream os;
        os << inverted;
        REQUIRE(os.str() == "0.1 px/mm");
    }
}

TEST_CASE("test_units/test_ratio | Compare ratios", "[units/ratio]") {
    auto r1 = math::ratio(1_mm, 8_px);
    auto r2 = math::ratio(2_mm, 8_px);
    REQUIRE(r1 > r2);
    REQUIRE(r1 >= r2);
    REQUIRE(r2 < r1);
    REQUIRE(r2 <= r1);
    REQUIRE(r1 != r2);
    REQUIRE(r1 == r1);
}

TEST_CASE("test_units/test_ratio | Apply ratio", "[units/ratio]") {
    auto ratio = math::types::RatioT(1_px, 10_mm);
    {
        std::ostringstream os;
        os << (ratio * 10_px);
        REQUIRE(os.str() == "100 mm");
    }
    {
        std::ostringstream os;
        os << (10_px * ratio);
        REQUIRE(os.str() == "100 mm");
    }
    {
        std::ostringstream os;
        os << (ratio * 10_mm);
        REQUIRE(os.str() == "1 px");
    }
    {
        std::ostringstream os;
        os << (10_mm * ratio);
        REQUIRE(os.str() == "1 px");
    }
}

TEST_CASE("test_units/test_ratio | Ratio at math scope (implicit units)", "[units/ratio]") {
    auto ratio = math::ratio(1_px, 10_mm);
    std::ostringstream os;
    os << ratio;
    REQUIRE(os.str() == "10 mm/px");
}

TEST_CASE("test_units/test_ratio | Some known ratios", "[units/ratio]") {
    {
        auto ratio = math::ratio<mm, m, float>();
        std::ostringstream os;
        os << ratio;
        REQUIRE(os.str() == "0.001 m/mm");
    }
    {
        auto ratio = math::ratio<m, mm, float>();
        std::ostringstream os;
        os << ratio;
        REQUIRE(os.str() == "1000 mm/m");
    }
}

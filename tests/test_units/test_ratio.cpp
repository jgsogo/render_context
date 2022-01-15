#include <sstream>
#include "catch2/catch.hpp"
#include "units/units.hpp"

using namespace math::units;

TEST_CASE("test_units/test_ratio | Ratio and print", "[units/ratio]") {
    auto ratio = math::types::RatioT<math::types::PixelsT, math::types::MilimetersT, float>(1_px, 10_mm);
    std::ostringstream os;
    os << ratio;
    REQUIRE(os.str() == "10 mm/px");
}

TEST_CASE("test_units/test_ratio | Ratio inverse", "[units/ratio]") {
    auto ratio = math::types::RatioT<math::types::PixelsT, math::types::MilimetersT, float>(1_px, 10_mm);
    std::ostringstream os;
    os << ratio.inverse();
    REQUIRE(os.str() == "0.1 px/mm");
}

TEST_CASE("test_units/test_ratio | Inverse ratio", "[units/ratio]") {
    using ForwardRatio = math::types::RatioT<math::types::PixelsT, math::types::MilimetersT, float>;
    using BackwardRatio = math::types::RatioT<math::types::MilimetersT, math::types::PixelsT, float>;
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

TEST_CASE("test_units/test_ratio | Apply ratio", "[units/ratio]") {
    auto ratio = math::types::RatioT<math::types::PixelsT, math::types::MilimetersT, float>(1_px, 10_mm);
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

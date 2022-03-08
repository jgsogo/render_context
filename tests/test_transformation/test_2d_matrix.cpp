#include <sstream>
#include "catch2/catch.hpp"
#include "units/milimeters.hpp"
#include "units/pixels.hpp"
#include "units/degrees.hpp"
#include "transformation/transformation.hpp"

using namespace math::units;


TEST_CASE("test_transformation/test_2d_matrix | Different unit types", "[transformation/2d]") {
    math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, double> m;

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > px] scale(1 px/mm), rotate(0), translate(0 px, 0 px)");
}

TEST_CASE("test_transformation/test_2d_matrix | Same unit type", "[transformation/2d]") {
    math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, double> m;

    std::ostringstream os;
    os << m;
    REQUIRE(os.str() == "[mm > mm] rotate(0), translate(0 mm, 0 mm)");
}

TEST_CASE("test_transformation/test_2d_matrix | Apply transformation with scale", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, float>;
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
    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, float>;
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

TEST_CASE("test_transformation/test_2d_matrix | Transform magnitude (with scale)", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, float>;
    TransformationType::Translation translation{10_px, 20_px};
    TransformationType::Scale scale = math::ratio(8_mm, 1_px);
    TransformationType::Rotation rotation{90.0_deg};
    auto m = TransformationType{translation, scale, rotation};

    auto px = m.transformMagnitude(16_mm);
    REQUIRE(px == 2_px);

    auto mm_ = m.transfromInverseMagnitude(10_px);
    REQUIRE(mm_ == 80_mm);
}

TEST_CASE("test_transformation/test_2d_matrix | Transform magnitude (without scale)", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Milimeters::symbol, float>;
    TransformationType::Translation translation{10_mm, 20_mm};
    TransformationType::Rotation rotation{90.0_deg};
    auto m = TransformationType{translation, rotation};

    auto px = m.transformMagnitude(16_mm);  // No scale :D
    REQUIRE(px == 16_mm);

    auto mm_ = m.transfromInverseMagnitude(10_mm);
    REQUIRE(mm_ == 10_mm);
}


TEST_CASE("test_transformation/test_2d_matrix | Set transformation elements (with scale)", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::Milimeters::symbol, math::Pixels::symbol, float>;
    auto m = TransformationType{};
    auto inputPoint = Magnum::Math::Vector2{1_mm, 0_mm};

    REQUIRE(m.getTranslation() == Magnum::Math::Vector2{0_px, 0_px});
    REQUIRE(m.getRotation() == 0_deg);
    REQUIRE(static_cast<float>(m.getScale()) == 1.f);

    m.set(TransformationType::Translation{10_px, 20_px});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{11_px, 20_px});
    REQUIRE(m.getTranslation() == Magnum::Math::Vector2{10_px, 20_px});

    m.set(TransformationType::Rotation{90_deg});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{10_px, 21_px});
    REQUIRE(m.getRotation() == 90_deg);

    m.set(TransformationType::Scale{math::ratio(8_mm, 1_px)});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{10_px, 20.125_px});
    REQUIRE(static_cast<float>(m.getScale()) == 0.125f);

    m.set(TransformationType::Translation{0_px, 0_px},
          TransformationType::Rotation{0_deg},
          math::ratio(1_mm, 1_px));
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{1_px, 0_px});

    // It can be applied on any order
    m.set(TransformationType::Rotation{90_deg},
          math::ratio(8_mm, 1_px),
          TransformationType::Translation{10_px, 20_px}
    );
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{10_px, 20.125_px});

    // We can skip some of them
    m.set(math::ratio(1_mm, 1_px),
          TransformationType::Translation{0_px, 0_px}
    );
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{0_px, 1_px});
}

TEST_CASE("test_transformation/test_2d_matrix | Set transformation elements (without scale)", "[transformation/2d]") {
    using TransformationType = math::xy::types::Transformation<math::Pixels::symbol, math::Pixels::symbol, float>;
    auto m = TransformationType{};
    auto inputPoint = Magnum::Math::Vector2{1_px, 0_px};

    REQUIRE(m.getTranslation() == Magnum::Math::Vector2{0_px, 0_px});
    REQUIRE(m.getRotation() == 0_deg);

    m.set(TransformationType::Translation{10_px, 20_px});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{11_px, 20_px});
    REQUIRE(m.getTranslation() == Magnum::Math::Vector2{10_px, 20_px});

    m.set(TransformationType::Rotation{90_deg});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{10_px, 21_px});
    REQUIRE(m.getRotation() == 90_deg);

    m.set(TransformationType::Translation{0_px, 0_px},
          TransformationType::Rotation{0_deg});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{1_px, 0_px});

    // It can be applied on any order
    m.set(TransformationType::Rotation{90_deg},
          TransformationType::Translation{10_px, 20_px});
    REQUIRE(m.transformPoint(inputPoint) == Magnum::Math::Vector2{10_px, 21_px});

}

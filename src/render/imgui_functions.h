#pragma once

#include <imgui.h>
#include <Magnum/Math/Vector2.h>

#include "../units/units.hpp"

namespace render::imgui {
    using Vector2Px = Magnum::Math::Vector2<math::Pixels>;

    void drawCircle(ImDrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness);

    void drawLine(ImDrawList &, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness);
}

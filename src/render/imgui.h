#pragma once

#include <Magnum/Math/Vector2.h>
//#include "imgui.h"
#include "units/units.hpp"
#include "units/pixels.hpp"

namespace render::imgui {
    /* ImGUI world uses float */

    using Pixels = math::types::PixelsT<float>;
    using Vector2Px = Magnum::Math::Vector2<Pixels>;

    void drawCircle(ImDrawList &drawList, const Vector2Px &center, Pixels radius, ImU32 color, float thickness);

}

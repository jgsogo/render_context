#include "imgui.h"

namespace render::imgui {

    void drawCircle(ImDrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, float thickness) {
        drawList.AddCircle(Magnum::Vector2{center}, (float) radius, color, 0, thickness);
    }

}

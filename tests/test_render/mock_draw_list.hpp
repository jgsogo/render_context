#pragma once

#include "render/context.h"

namespace mocks {

    struct DrawList {

    };
}

namespace render {

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<mocks::DrawList>(mocks::DrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness) {

    }

    /*
    template<>
    void drawLine<ImDrawList>(ImDrawList &, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness);

    template<>
    void drawRectangle<ImDrawList>(ImDrawList &, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color, math::Pixels thickness);

    template<>
    void drawRectangleFilled<ImDrawList>(ImDrawList &, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color);

    template<>
    void drawPolyline<ImDrawList>(ImDrawList &, const std::vector<Vector2Px> &points_, ImU32 color, math::Pixels thickness, int flags);

    template<>
    void drawPolylineFilled<ImDrawList>(ImDrawList &, std::vector<Vector2Px> points_, ImU32 color);

    template<>
    void drawText<ImDrawList>(ImDrawList &, Vector2Px position_, float fontSize_, ImU32 color, const std::string &content);

    template<>
    void drawImage<ImDrawList>(ImDrawList &, Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<math::Pixels> uvCoords,
                               std::array<Vector2Px, 4> bbox);
    */

}
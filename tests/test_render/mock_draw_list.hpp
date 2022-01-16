#pragma once

#include "render/context.h"

namespace mocks {

    struct DrawList {
        std::vector<std::tuple<render::Vector2Px, math::Pixels, ImU32, math::Pixels>> drawCircle;
        std::vector<std::tuple<render::Vector2Px, render::Vector2Px, ImU32, math::Pixels>> drawLine;
        std::vector<std::tuple<Magnum::Math::Range2D<math::Pixels>, ImU32, math::Pixels>> drawRectangle;
        std::vector<std::tuple<Magnum::Math::Range2D<math::Pixels>, ImU32>> drawRectangleFilled;
        std::vector<std::tuple<std::vector<render::Vector2Px>, ImU32, math::Pixels, int>> drawPolyline;
        std::vector<std::tuple<std::vector<render::Vector2Px>, ImU32>> drawPolylineFilled;
        std::vector<std::tuple<render::Vector2Px, float, ImU32, std::string>> drawText;
        //std::vector<std::tuple<Magnum::GL::Texture2D, Magnum::Math::Range2D<math::Pixels>, std::array<render::Vector2Px, 4>>> drawImage;
    };
}

namespace render {

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<mocks::DrawList>(mocks::DrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness) {
        drawList.drawCircle.emplace_back(center, radius, color, thickness);
    }

    template<>
    void drawLine<mocks::DrawList>(mocks::DrawList &drawList, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness) {
        drawList.drawLine.emplace_back(start, end, color, thickness);
    }

    template<>
    void drawRectangle<mocks::DrawList>(mocks::DrawList &drawList, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color, math::Pixels thickness) {
        drawList.drawRectangle.emplace_back(rectangle, color, thickness);
    }

    template<>
    void drawRectangleFilled<mocks::DrawList>(mocks::DrawList &drawList, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color) {
        drawList.drawRectangleFilled.emplace_back(rectangle, color);
    }

    template<>
    void drawPolyline<mocks::DrawList>(mocks::DrawList &drawList, const std::vector<Vector2Px> &points_, ImU32 color, math::Pixels thickness, int flags) {
        drawList.drawPolyline.emplace_back(points_, color, thickness, flags);
    }

    template<>
    void drawPolylineFilled<mocks::DrawList>(mocks::DrawList &drawList, std::vector<Vector2Px> points_, ImU32 color) {
        drawList.drawPolylineFilled.emplace_back(points_, color);
    }

    template<>
    void drawText<mocks::DrawList>(mocks::DrawList &drawList, Vector2Px position_, float fontSize_, ImU32 color, const std::string &content) {
        drawList.drawText.emplace_back(position_, fontSize_, color, content);
    }

    template<>
    void drawImage<mocks::DrawList>(mocks::DrawList &drawList, Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<math::Pixels> uvCoords,
                                    std::array<Vector2Px, 4> bbox) {
        //drawList.drawImage.emplace_back(texture, uvCoords, bbox);
    }
}
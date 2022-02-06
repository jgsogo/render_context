#pragma once

#include "render/context.h"

namespace mocks {

    struct DrawList {
        std::vector<std::tuple<Magnum::Math::Vector2<math::Pixels>, math::Pixels, ImU32, math::Pixels>> drawCircle;
        std::vector<std::tuple<Magnum::Math::Vector2<math::Pixels>, Magnum::Math::Vector2<math::Pixels>, ImU32, math::Pixels>> drawLine;
        std::vector<std::tuple<Magnum::Math::Range2D<math::Pixels>, ImU32, math::Pixels>> drawRectangle;
        std::vector<std::tuple<Magnum::Math::Range2D<math::Pixels>, ImU32>> drawRectangleFilled;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<math::Pixels>>, ImU32, math::Pixels, int>> drawPolyline;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<math::Pixels>>, ImU32>> drawPolylineFilled;
        std::vector<std::tuple<Magnum::Math::Vector2<math::Pixels>, float, ImU32, std::string>> drawText;
        std::vector<std::tuple<Magnum::GL::Texture2D &, Magnum::Math::Range2D<render::UVCoordinates>, std::array<Magnum::Math::Vector2<math::Pixels>, 4>>> drawImage;
    };
}

namespace render {

    /* Overrides for _draw..._ functions */
    template<>
    inline void drawCircle<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                          const Magnum::Math::Vector2<math::Pixels> &center,
                                                          math::Pixels radius, ImU32 color,
                                                          math::Pixels thickness) {
        drawList.drawCircle.emplace_back(center, radius, color, thickness);
    }

    template<>
    inline void drawLine<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                        const Magnum::Math::Vector2<math::Pixels> &start,
                                                        const Magnum::Math::Vector2<math::Pixels> &end,
                                                        ImU32 color,
                                                        math::Pixels thickness) {
        drawList.drawLine.emplace_back(start, end, color, thickness);
    }

    template<>
    inline void drawRectangle<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                             Magnum::Math::Range2D<math::Pixels> rectangle,
                                                             ImU32 color,
                                                             math::Pixels thickness) {
        drawList.drawRectangle.emplace_back(rectangle, color, thickness);
    }

    template<>
    inline void drawRectangleFilled<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                                   Magnum::Math::Range2D<math::Pixels> rectangle,
                                                                   ImU32 color) {
        drawList.drawRectangleFilled.emplace_back(rectangle, color);
    }

    template<>
    inline void drawPolyline<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                            const std::vector<Magnum::Math::Vector2<math::Pixels>> &points_,
                                                            ImU32 color,
                                                            math::Pixels thickness,
                                                            int flags) {
        drawList.drawPolyline.emplace_back(points_, color, thickness, flags);
    }

    template<>
    inline void drawPolylineFilled<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                                  std::vector<Magnum::Math::Vector2<math::Pixels>> points_,
                                                                  ImU32 color) {
        drawList.drawPolylineFilled.emplace_back(points_, color);
    }

    template<>
    inline void drawText<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                        Magnum::Math::Vector2<math::Pixels> position_,
                                                        float fontSize_,
                                                        ImU32 color,
                                                        const std::string &content) {
        drawList.drawText.emplace_back(position_, fontSize_, color, content);
    }

    template<>
    inline void drawImage<mocks::DrawList, math::Pixels>(mocks::DrawList &drawList,
                                                         Magnum::GL::Texture2D &texture,
                                                         const Magnum::Math::Range2D<UVCoordinates> &uvCoords,
                                                         const std::array<Magnum::Math::Vector2<math::Pixels>, 4> &bbox) {
        drawList.drawImage.emplace_back(texture, uvCoords, bbox);
    }
}
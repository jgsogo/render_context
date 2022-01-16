#pragma once

#include "render/context.h"

namespace mocks {

    struct DrawList {
        std::vector<std::tuple<Magnum::Math::Vector2<float>, float, ImU32, float>> drawCircle;
        std::vector<std::tuple<Magnum::Math::Vector2<float>, Magnum::Math::Vector2<float>, ImU32, float>> drawLine;
        std::vector<std::tuple<Magnum::Math::Range2D<float>, ImU32, float>> drawRectangle;
        std::vector<std::tuple<Magnum::Math::Range2D<float>, ImU32>> drawRectangleFilled;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<float>>, ImU32, float, int>> drawPolyline;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<float>>, ImU32>> drawPolylineFilled;
        std::vector<std::tuple<Magnum::Math::Vector2<float>, float, ImU32, std::string>> drawText;
        //std::vector<std::tuple<Magnum::GL::Texture2D, Magnum::Math::Range2D<float>, std::array<render::Vector2Px, 4>>> drawImage;
    };
}

namespace render {

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<mocks::DrawList, float>(mocks::DrawList &drawList,
                                            const Magnum::Math::Vector2<float> &center,
                                            float radius, ImU32 color,
                                            float thickness) {
        drawList.drawCircle.emplace_back(center, radius, color, thickness);
    }

    template<>
    void drawLine<mocks::DrawList, float>(mocks::DrawList &drawList,
                                          const Magnum::Math::Vector2<float> &start,
                                          const Magnum::Math::Vector2<float> &end,
                                          ImU32 color,
                                          float thickness) {
        drawList.drawLine.emplace_back(start, end, color, thickness);
    }

    template<>
    void drawRectangle<mocks::DrawList, float>(mocks::DrawList &drawList,
                                               Magnum::Math::Range2D<float> rectangle,
                                               ImU32 color,
                                               float thickness) {
        drawList.drawRectangle.emplace_back(rectangle, color, thickness);
    }

    template<>
    void drawRectangleFilled<mocks::DrawList, float>(mocks::DrawList &drawList,
                                                     Magnum::Math::Range2D<float> rectangle,
                                                     ImU32 color) {
        drawList.drawRectangleFilled.emplace_back(rectangle, color);
    }

    template<>
    void drawPolyline<mocks::DrawList, float>(mocks::DrawList &drawList,
                                              const std::vector<Magnum::Math::Vector2<float>> &points_,
                                              ImU32 color,
                                              float thickness,
                                              int flags) {
        drawList.drawPolyline.emplace_back(points_, color, thickness, flags);
    }

    template<>
    void drawPolylineFilled<mocks::DrawList, float>(mocks::DrawList &drawList,
                                                    std::vector<Magnum::Math::Vector2<float>> points_,
                                                    ImU32 color) {
        drawList.drawPolylineFilled.emplace_back(points_, color);
    }

    template<>
    void drawText<mocks::DrawList, float>(mocks::DrawList &drawList,
                                          Magnum::Math::Vector2<float> position_,
                                          float fontSize_,
                                          ImU32 color,
                                          const std::string &content) {
        drawList.drawText.emplace_back(position_, fontSize_, color, content);
    }

    template<>
    void drawImage<mocks::DrawList, float>(mocks::DrawList &drawList,
                                           Magnum::GL::Texture2D &texture,
                                           Magnum::Math::Range2D<float> uvCoords,
                                           std::array<Magnum::Math::Vector2<float>, 4> bbox) {
        //drawList.drawImage.emplace_back(texture, uvCoords, bbox);
    }
}
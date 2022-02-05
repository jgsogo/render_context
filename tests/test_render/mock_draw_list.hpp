#pragma once

#include "render/context.h"

namespace mocks {

    template<typename T>
    struct DrawList {
        std::vector<std::tuple<Magnum::Math::Vector2<T>, T, ImU32, float>> drawCircle;
        std::vector<std::tuple<Magnum::Math::Vector2<T>, Magnum::Math::Vector2<float>, ImU32, float>> drawLine;
        std::vector<std::tuple<Magnum::Math::Range2D<T>, ImU32, float>> drawRectangle;
        std::vector<std::tuple<Magnum::Math::Range2D<T>, ImU32>> drawRectangleFilled;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<T>>, ImU32, float, int>> drawPolyline;
        std::vector<std::tuple<std::vector<Magnum::Math::Vector2<T>>, ImU32>> drawPolylineFilled;
        std::vector<std::tuple<Magnum::Math::Vector2<T>, float, ImU32, std::string>> drawText;
        std::vector<std::tuple<Magnum::GL::Texture2D, Magnum::Math::Range2D<render::UVCoordinates>, std::array<Magnum::Math::Vector2<T>, 4>>> drawImage;
    };
}

namespace render {

    /* Overrides for _draw..._ functions */
    template<typename T>
    void drawCircle<mocks::DrawList, T>(mocks::DrawList<T> &drawList,
                                        const Magnum::Math::Vector2<T> &center,
                                        T radius, ImU32 color,
                                        float thickness) {
        drawList.drawCircle.emplace_back(center, radius, color, thickness);
    }

    template<typename T>
    void drawLine<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                          const Magnum::Math::Vector2<T> &start,
                                          const Magnum::Math::Vector2<T> &end,
                                          ImU32 color,
                                          float thickness) {
        drawList.drawLine.emplace_back(start, end, color, thickness);
    }

    template<typename T>
    void drawRectangle<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                               Magnum::Math::Range2D<T> rectangle,
                                               ImU32 color,
                                               float thickness) {
        drawList.drawRectangle.emplace_back(rectangle, color, thickness);
    }

    template<typename T>
    void drawRectangleFilled<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                                     Magnum::Math::Range2D<T> rectangle,
                                                     ImU32 color) {
        drawList.drawRectangleFilled.emplace_back(rectangle, color);
    }

    template<typename T>
    void drawPolyline<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                              const std::vector<Magnum::Math::Vector2<T>> &points_,
                                              ImU32 color,
                                              float thickness,
                                              int flags) {
        drawList.drawPolyline.emplace_back(points_, color, thickness, flags);
    }

    template<typename T>
    void drawPolylineFilled<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                                    std::vector<Magnum::Math::Vector2<T>> points_,
                                                    ImU32 color) {
        drawList.drawPolylineFilled.emplace_back(points_, color);
    }

    template<typename T>
    void drawText<mocks::DrawList, float>(mocks::DrawList<T> &drawList,
                                          Magnum::Math::Vector2<T> position_,
                                          float fontSize_,
                                          ImU32 color,
                                          const std::string &content) {
        drawList.drawText.emplace_back(position_, fontSize_, color, content);
    }

    template<typename T>
    void drawImage<mocks::DrawList>(mocks::DrawList<T> &drawList, Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<UVCoordinates> uvCoords,
                                    std::array<Magnum::Math::Vector2<T>, 4> bbox) {
        drawList.drawImage.emplace_back(texture, uvCoords, bbox);
    }
}
#pragma once

#include "../context.h"

namespace render {

    template<const char *Origin, const char *PixelsSymbol = math::units::px>
    using ImGuiContext = Context<Origin, ImDrawList, PixelsSymbol>;

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<ImDrawList, float>(ImDrawList &drawList,
                                       const Magnum::Math::Vector2<float> &center,
                                       float radius,
                                       ImU32 color,
                                       float thickness);

    template<>
    void drawLine<ImDrawList, float>(ImDrawList &drawList,
                                     const Magnum::Math::Vector2<float> &start,
                                     const Magnum::Math::Vector2<float> &end,
                                     ImU32 color,
                                     float thickness);

    template<>
    void drawRectangle<ImDrawList, float>(ImDrawList &drawList,
                                          Magnum::Math::Range2D<float> rectangle,
                                          ImU32 color,
                                          float thickness);

    template<>
    void drawRectangleFilled<ImDrawList, float>(ImDrawList &drawList,
                                                Magnum::Math::Range2D<float> rectangle,
                                                ImU32 color);

    template<>
    void drawPolyline<ImDrawList, float>(ImDrawList &drawList,
                                         const std::vector<Magnum::Math::Vector2<float>> &points_,
                                         ImU32 color,
                                         float thickness,
                                         int flags);

    template<>
    void drawPolylineFilled<ImDrawList, float>(ImDrawList &drawList,
                                               std::vector<Magnum::Math::Vector2<float>> points_,
                                               ImU32 color);

    template<>
    void drawText<ImDrawList, float>(ImDrawList &drawList,
                                     Magnum::Math::Vector2<float> position,
                                     float fontSize,
                                     ImU32 color,
                                     const std::string &content);

    template<>
    void drawImage<ImDrawList, float>(ImDrawList &drawList,
                                      Magnum::GL::Texture2D &texture,
                                      const Magnum::Math::Range2D<UVCoordinates> &uvCoords,
                                      const std::array<Magnum::Math::Vector2<float>, 4> &bbox) {
        // Draw translated-rotated image: https://github.com/ocornut/imgui/issues/1982
        ImVec2 uvs[4] = {Magnum::Math::Vector2<float>{uvCoords.topLeft()},
                         Magnum::Math::Vector2<float>{uvCoords.topRight()},
                         Magnum::Math::Vector2<float>{uvCoords.bottomRight()},
                         Magnum::Math::Vector2<float>{uvCoords.bottomLeft()}
        };
        drawList.AddImageQuad(&texture,
                              bbox[0], bbox[1], bbox[2], bbox[3],
                              uvs[0], uvs[1], uvs[2], uvs[3],
                              IM_COL32_WHITE);
    }
}

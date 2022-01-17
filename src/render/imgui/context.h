#pragma once

#include "../context.h"

namespace render {

    template<const char *Origin>
    using ImGuiContext = Context<Origin, ImDrawList>;

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<ImDrawList>(ImDrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness) {
        drawList.AddCircle(center, (float) radius, color, 0, (float) thickness);
    }

    template<>
    void drawLine<ImDrawList>(ImDrawList &drawList, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness) {
        drawList.AddLine(start, end, color, (float) thickness);
    }

    template<>
    void drawRectangle<ImDrawList>(ImDrawList &drawList, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color, math::Pixels thickness) {
        drawList.AddRect(rectangle.topLeft(), rectangle.bottomRight(), color, 0, 0, (float) thickness);
    }

    template<>
    void drawRectangleFilled<ImDrawList>(ImDrawList &drawList, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color) {
        drawList.AddRectFilled(rectangle.topLeft(), rectangle.bottomRight(), color);
    }

    template<>
    void drawPolyline<ImDrawList>(ImDrawList &drawList, const std::vector<Vector2Px> &points_, ImU32 color, math::Pixels thickness, int flags) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return Magnum::Vector2{item};
        });
        drawList.AddPolyline(points.data(), points.size(), color, flags, (float) thickness);
    }

    template<>
    void drawPolylineFilled<ImDrawList>(ImDrawList &drawList, std::vector<Vector2Px> points_, ImU32 color) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return Magnum::Vector2{item};
        });
        drawList.AddConvexPolyFilled(points.data(), points.size(), color);
    }

    template<>
    void drawText<ImDrawList>(ImDrawList &drawList, Vector2Px position, float fontSize, ImU32 color, const std::string &content) {
        // TODO: If we want to rotate, we need to move vertices ourselves: https://gist.github.com/carasuca/e72aacadcf6cf8139de46f97158f790f
        // TODO: Compute centered in a better way (use ImGui::CalcTextSize())
        drawList.AddText(ImGui::GetFont(), fontSize, Magnum::Vector2{position}, color, content.c_str());
        /*
        Magnum::Vector2 centered{
                (float) position_.x() - (content.size() * fontSize_ / 4.f),
                (float) position_.y() - (fontSize_ / 2.f),
        };
        auto position = _transform.transformPoint(Magnum::Vector2{centered});
        float fontSize = (float) fontSize_ * _transform.uniformScaling();
        drawList.AddText(ImGui::GetFont(), fontSize, position, color, content.c_str());
         */
    }

    template<>
    void drawImage<ImDrawList>(ImDrawList &drawList, Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<math::Pixels> uvCoords,
                               std::array<Vector2Px, 4> bbox) {
        // Draw translated-rotated image: https://github.com/ocornut/imgui/issues/1982
        ImVec2 uvs[4] = {uvCoords.topLeft(),
                         uvCoords.topRight(),
                         uvCoords.bottomRight(),
                         uvCoords.bottomLeft()
        };
        drawList.AddImageQuad(&texture,
                              bbox[0], bbox[1], bbox[2], bbox[3],
                              uvs[0], uvs[1], uvs[2], uvs[3],
                              IM_COL32_WHITE);
    }
}

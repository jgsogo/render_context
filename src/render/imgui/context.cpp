#include "context.h"

namespace render {

    template<>
    void drawCircle<ImDrawList, float>(ImDrawList &drawList,
                                       const Magnum::Math::Vector2<float> &center,
                                       float radius,
                                       ImU32 color,
                                       float thickness) {
        drawList.AddCircle(center, radius, color, 0, thickness);
    }

    template<>
    void drawLine<ImDrawList, float>(ImDrawList &drawList,
                                     const Magnum::Math::Vector2<float> &start,
                                     const Magnum::Math::Vector2<float> &end,
                                     ImU32 color,
                                     float thickness) {
        drawList.AddLine(start, end, color, thickness);
    }

    template<>
    void drawRectangle<ImDrawList, float>(ImDrawList &drawList,
                                          Magnum::Math::Range2D<float> rectangle,
                                          ImU32 color,
                                          float thickness) {
        drawList.AddRect(rectangle.topLeft(), rectangle.bottomRight(), color, 0, 0, thickness);
    }

    template<>
    void drawRectangleFilled<ImDrawList, float>(ImDrawList &drawList,
                                                Magnum::Math::Range2D<float> rectangle,
                                                ImU32 color) {
        drawList.AddRectFilled(rectangle.topLeft(), rectangle.bottomRight(), color);
    }

    template<>
    void drawPolyline<ImDrawList, float>(ImDrawList &drawList,
                                         const std::vector<Magnum::Math::Vector2<float>> &points_,
                                         ImU32 color,
                                         float thickness,
                                         int flags) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return Magnum::Vector2{item};
        });
        drawList.AddPolyline(points.data(), points.size(), color, flags, thickness);
    }

    template<>
    void drawPolylineFilled<ImDrawList, float>(ImDrawList &drawList,
                                               std::vector<Magnum::Math::Vector2<float>> points_,
                                               ImU32 color) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return Magnum::Vector2{item};
        });
        drawList.AddConvexPolyFilled(points.data(), points.size(), color);
    }

    template<>
    void drawText<ImDrawList, float>(ImDrawList &drawList,
                                     Magnum::Math::Vector2<float> position,
                                     float fontSize,
                                     ImU32 color,
                                     const std::string &content) {
        // TODO: If we want to rotate, we need to move vertices ourselves: https://gist.github.com/carasuca/e72aacadcf6cf8139de46f97158f790f
        // TODO: Compute centered in a better way (use ImGui::CalcTextSize())
        drawList.AddText(ImGui::GetFont(), fontSize, position, color, content.c_str());
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
}

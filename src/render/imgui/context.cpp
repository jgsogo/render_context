#include "context.h"

namespace render {

    template<>
    void drawCircle<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                               const Magnum::Math::Vector2<imgui::Pixels> &center,
                                               imgui::Pixels radius,
                                               ImU32 color,
                                               imgui::Pixels thickness) {
        drawList.AddCircle(center, static_cast<float>(radius), color, 0, static_cast<float>(thickness));
    }

    template<>
    void drawLine<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                             const Magnum::Math::Vector2<imgui::Pixels> &start,
                                             const Magnum::Math::Vector2<imgui::Pixels> &end,
                                             ImU32 color,
                                             imgui::Pixels thickness) {
        drawList.AddLine(start, end, color, static_cast<float>(thickness));
    }

    template<>
    void drawRectangle<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                  Magnum::Math::Range2D<imgui::Pixels> rectangle,
                                                  ImU32 color,
                                                  imgui::Pixels thickness) {
        drawList.AddRect(rectangle.topLeft(), rectangle.bottomRight(), color, 0, 0, static_cast<float>(thickness));
    }

    template<>
    void drawRectangleFilled<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                        Magnum::Math::Range2D<imgui::Pixels> rectangle,
                                                        ImU32 color) {
        drawList.AddRectFilled(rectangle.topLeft(), rectangle.bottomRight(), color);
    }

    template<>
    void drawPolyline<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                 const std::vector<Magnum::Math::Vector2<imgui::Pixels>> &points_,
                                                 ImU32 color,
                                                 imgui::Pixels thickness,
                                                 int flags) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return Magnum::Vector2{item};
        });
        drawList.AddPolyline(points.data(), points.size(), color, flags, static_cast<float>(thickness));
    }

    template<>
    void drawPolylineFilled<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                       std::vector<Magnum::Math::Vector2<imgui::Pixels>> points_,
                                                       ImU32 color) {
        std::vector<ImVec2> points;
        std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
            return item;
        });
        drawList.AddConvexPolyFilled(points.data(), points.size(), color);
    }

    template<>
    void drawText<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                             Magnum::Math::Vector2<imgui::Pixels> position,
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

    template<>
    void drawImage<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                              Magnum::GL::Texture2D &texture,
                                              const Magnum::Math::Range2D<UVCoordinates> &uvCoords,
                                              const std::array<Magnum::Math::Vector2<imgui::Pixels>, 4> &bbox) {
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

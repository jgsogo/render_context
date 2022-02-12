#pragma once

#include "../context.h"

namespace render {

    template<const char *Origin>
    using ImGuiContext = Context<Origin, ImDrawList, imgui::units::impx>;

    /* Overrides for _draw..._ functions */
    template<>
    void drawCircle<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                               const Magnum::Math::Vector2<imgui::Pixels> &center,
                                               imgui::Pixels radius,
                                               ImU32 color,
                                               imgui::Pixels thickness);

    template<>
    void drawLine<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                             const Magnum::Math::Vector2<imgui::Pixels> &start,
                                             const Magnum::Math::Vector2<imgui::Pixels> &end,
                                             ImU32 color,
                                             imgui::Pixels thickness);

    template<>
    void drawRectangle<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                  Magnum::Math::Range2D<imgui::Pixels> rectangle,
                                                  ImU32 color,
                                                  imgui::Pixels thickness);

    template<>
    void drawRectangleFilled<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                        Magnum::Math::Range2D<imgui::Pixels> rectangle,
                                                        ImU32 color);

    template<>
    void drawPolyline<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                 const std::vector<Magnum::Math::Vector2<imgui::Pixels>> &points_,
                                                 ImU32 color,
                                                 imgui::Pixels thickness,
                                                 int flags);

    template<>
    void drawPolylineFilled<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                                       std::vector<Magnum::Math::Vector2<imgui::Pixels>> points_,
                                                       ImU32 color);

    template<>
    void drawText<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                             Magnum::Math::Vector2<imgui::Pixels> position,
                                             float fontSize,
                                             ImU32 color,
                                             const std::string &content);

    template<>
    void drawImage<ImDrawList, imgui::Pixels>(ImDrawList &drawList,
                                              Magnum::GL::Texture2D &texture,
                                              const Magnum::Math::Range2D<UVCoordinates> &uvCoords,
                                              const std::array<Magnum::Math::Vector2<imgui::Pixels>, 4> &bbox);
}

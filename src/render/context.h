#pragma once

#include <vector>
#include <array>
#include <imgui.h>  // TOOD: Get rid of everything imgui-related
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Range.h>
#include <Magnum/GL/Texture.h>

#include "../transformation/transformation.hpp"

namespace render {
    using Vector2Px = Magnum::Math::Vector2<math::Pixels>;

    template<typename TDrawList>
    void drawCircle(TDrawList &drawList, const Vector2Px &center, math::Pixels radius, ImU32 color, math::Pixels thickness);

    template<typename TDrawList>
    void drawLine(TDrawList &, const Vector2Px &start, const Vector2Px &end, ImU32 color, math::Pixels thickness);

    template<typename TDrawList>
    void drawRectangle(TDrawList &, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color, math::Pixels thickness);

    template<typename TDrawList>
    void drawRectangleFilled(TDrawList &, Magnum::Math::Range2D<math::Pixels> rectangle, ImU32 color);

    template<typename TDrawList>
    void drawPolyline(TDrawList &, const std::vector<Vector2Px> &points_, ImU32 color, math::Pixels thickness, int flags = 0);

    template<typename TDrawList>
    void drawPolylineFilled(TDrawList &, std::vector<Vector2Px> points_, ImU32 color);

    template<typename TDrawList>
    void drawText(TDrawList &, Vector2Px position_, float fontSize_, ImU32 color, const std::string &content);

    template<typename TDrawList>
    void drawImage(TDrawList &, Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<math::Pixels> uvCoords,
                   std::array<Vector2Px, 4> bbox);

    template<const char *Origin, typename TDrawList>
    class Context {
        using OriginUnits = ::math::types::NamedUnitT<float, Origin>;
        using Vector2Ori = Magnum::Math::Vector2<OriginUnits>;
    public:
        explicit Context(TDrawList &dl, int lodLevel = 0) : _drawList{dl}, _lod{lodLevel} {
        }

        template<const char *Other>
        Context<Other, TDrawList> operator<<(const math::xy::types::Transformation<Other, Origin, float> &tf) const {
            Context<Other, TDrawList> ctxt{_drawList, _lod};
            ctxt._transformation = _transformation * tf;
            return ctxt;
        }

        /* Draw functions */

        void drawCircle(Vector2Ori center, OriginUnits radius, ImU32 color, math::Pixels thickness) {
            auto rpx = _transformation.transformMagnitude(radius);
            auto centerpx = _transformation.transformPoint(center);
            render::drawCircle<TDrawList>(_drawList, centerpx, rpx, color, thickness);
        }

        void drawLine(Vector2Ori ini, Vector2Ori end, ImU32 color, math::Pixels thickness) {
            auto iniPoint = _transformation.transformPoint(ini);
            auto endPoint = _transformation.transformPoint(end);
            render::drawLine<TDrawList>(_drawList, iniPoint, endPoint, color, thickness);
        }

        void drawRectangle(Magnum::Math::Range2D<OriginUnits> rectangle, ImU32 color, math::Pixels thickness) {
            // TODO: (Optimize) if no rotation, just call 'drawRectangle'
            std::vector<Vector2Ori> points = {
                    rectangle.topLeft(),
                    rectangle.topRight(),
                    rectangle.bottomRight(),
                    rectangle.bottomLeft()
            };
            this->drawPolyline(points, color, thickness, ImDrawFlags_Closed);
        }

        void drawRectangleFilled(Magnum::Math::Range2D<OriginUnits> rectangle, ImU32 color) {
            // TODO: (Optimize) if no rotation, just call 'drawRectangleFilled'
            std::vector<Vector2Ori> points = {
                    rectangle.topLeft(),
                    rectangle.topRight(),
                    rectangle.bottomRight(),
                    rectangle.bottomLeft()
            };
            this->drawPolylineFilled(points, color);
        }

        void drawPolyline(std::vector<Vector2Ori> points_,
                          ImU32 color, math::Pixels thickness, int flags) {
            std::vector<Vector2Px> points;
            std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
                return _transformation.transformPoint(item);
            });
            render::drawPolyline<TDrawList>(_drawList, points, color, thickness, flags);
        }

        void drawPolylineFilled(std::vector<Vector2Ori> points_, ImU32 color) {
            std::vector<Vector2Px> points;
            std::transform(points_.begin(), points_.end(), std::back_inserter(points), [&](auto &item) {
                return _transformation.transformPoint(item);
            });
            render::drawPolylineFilled<TDrawList>(_drawList, points, color);
        }

        void drawText(Vector2Ori position, float fontSize_, ImU32 color, const std::string &content) {
            // TODO: Center text in coordinates?
            auto pospx = _transformation.transformPoint(position);
            render::drawText<TDrawList>(_drawList, pospx, fontSize_, color, content);
        }

        void drawImage(Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<math::Pixels> uvCoords,
                       Magnum::Math::Range2D<OriginUnits> bbox_) {
            std::array<Vector2Px, 4> bbox = {
                    _transformation.transformPoint(bbox_.topLeft()),
                    _transformation.transformPoint(bbox_.topRight()),
                    _transformation.transformPoint(bbox_.bottomRight()),
                    _transformation.transformPoint(bbox_.bottomLeft())
            };
            render::drawImage<TDrawList>(_drawList, texture, uvCoords, bbox);
        }

    protected:
        TDrawList &_drawList;
        int _lod = 0;
        math::xy::types::Transformation<Origin, math::Pixels::symbol, float> _transformation;
    };
}

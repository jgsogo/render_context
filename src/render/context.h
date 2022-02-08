#pragma once

#include <vector>
#include <array>
#include <imgui.h>  // TODO: Get rid of everything imgui-related
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Range.h>
#include <Magnum/GL/Texture.h>

#include "../transformation/transformation.hpp"
#include "../units/pixels.hpp"

namespace render {
    namespace units {
        static constexpr char uv[] = "uv";
    }

    using UVCoordinates = math::types::NamedUnitT<float, units::uv>;

    namespace units {
        constexpr UVCoordinates operator "" _uv(long double d) {
            return UVCoordinates{static_cast<float>(d)};
        }

        constexpr UVCoordinates operator "" _uv(unsigned long long d) {
            return UVCoordinates{static_cast<float>(d)};
        }
    }

    template<typename TDrawList, typename T>
    void drawCircle(TDrawList &drawList, const Magnum::Math::Vector2<T> &center, T radius, ImU32 color, T thickness);

    template<typename TDrawList, typename T>
    void drawLine(TDrawList &, const Magnum::Math::Vector2<T> &start, const Magnum::Math::Vector2<T> &end, ImU32 color, T thickness);

    template<typename TDrawList, typename T>
    void drawRectangle(TDrawList &, Magnum::Math::Range2D<T> rectangle, ImU32 color, T thickness);

    template<typename TDrawList, typename T>
    void drawRectangleFilled(TDrawList &, Magnum::Math::Range2D<T> rectangle, ImU32 color);

    template<typename TDrawList, typename T>
    void drawPolyline(TDrawList &, const std::vector<Magnum::Math::Vector2<T>> &points_, ImU32 color, T thickness, int flags = 0);

    template<typename TDrawList, typename T>
    void drawPolylineFilled(TDrawList &, std::vector<Magnum::Math::Vector2<T>> points_, ImU32 color);

    template<typename TDrawList, typename T>
    void drawText(TDrawList &, Magnum::Math::Vector2<T> position_, float fontSize_, ImU32 color, const std::string &content);

    template<typename TDrawList, typename T>
    void drawImage(TDrawList &, Magnum::GL::Texture2D &texture, const Magnum::Math::Range2D<UVCoordinates> &uvCoords,
                   const std::array<Magnum::Math::Vector2<T>, 4> &bbox);

    template<const char *Origin, typename TDrawList, const char *PixelsSymbol = ::math::units::px>
    class Context {
    public:
        using OriginUnits = ::math::types::NamedUnitT<float, Origin>;
        using PixelUnits = ::math::types::NamedUnitT<float, PixelsSymbol>;
        using Vector2Ori = Magnum::Math::Vector2<OriginUnits>;
        using Vector2Px = Magnum::Math::Vector2<PixelUnits>;
    public:
        explicit Context(TDrawList &dl, int lodLevel = 0) : _drawList{dl}, _lod{lodLevel} {
        }

        template<typename ...Args>
        explicit Context(TDrawList &dl, int lodLevel = 0, Args &&... args)
                : _drawList{dl}, _lod{lodLevel}, _transformation{std::forward<Args>(args)...} {
        }

        template<const char *Other>
        Context<Other, TDrawList, PixelsSymbol> operator<<(const math::xy::types::Transformation<Other, Origin, float> &tf) const {
            Context<Other, TDrawList, PixelsSymbol> ctxt{_drawList, _lod, _transformation * tf};
            return ctxt;
        }

        Vector2Ori transformInverse(const Magnum::Math::Vector2<math::Pixels> &in) {
            return _transformation.transformInverse(in);
        }

        /* Draw functions */

        void drawCircle(Vector2Ori center, OriginUnits radius, ImU32 color, PixelUnits thickness) {
            auto rpx = _transformation.transformMagnitude(radius);
            auto centerpx = _transformation.transformPoint(center);
            render::drawCircle<TDrawList>(_drawList, centerpx, rpx, color, thickness);
        }

        void drawLine(Vector2Ori ini, Vector2Ori end, ImU32 color, PixelUnits thickness) {
            auto iniPoint = _transformation.transformPoint(ini);
            auto endPoint = _transformation.transformPoint(end);
            render::drawLine<TDrawList>(_drawList, iniPoint, endPoint, color, thickness);
        }

        void drawRectangle(Magnum::Math::Range2D<OriginUnits> rectangle, ImU32 color, PixelUnits thickness) {
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

        void drawPolyline(std::vector<Vector2Ori> points_, ImU32 color, PixelUnits thickness, int flags) {
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

        void drawImage(Magnum::GL::Texture2D &texture, Magnum::Math::Range2D<UVCoordinates> uvCoords,
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
        math::xy::types::Transformation<Origin, PixelsSymbol, float> _transformation;
    };
}

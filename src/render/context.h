#pragma once

#include "units/units.hpp"
#include "transformation/transformation.hpp"

#include "imgui.h"

namespace render {

    template<template<typename> typename Origin,
            typename T = float>
    class Context {
    public:
        explicit Context(ImDrawList &dl, int lodLevel = 0) : _drawList{dl}, _lod{lodLevel} {
        }

        void drawCircle(Origin<T> radius, ImU32 color, float thickness) {
            auto r = _transformation.transformMagnitude(radius);
            // TODO: Too many casts
            auto center = transformation.transformPoint(Magnum::Math::Vector2{Magnum::Math::ZeroInit});
            imgui::drawCircle(_drawList, center, radius, color, (float) thickness);
        }

    protected:
        ImDrawList &_drawList;
        int _lod = 0;
        math::Transformation2D<Origin, math::types::PixelsT, T> _transformation;
    };
}
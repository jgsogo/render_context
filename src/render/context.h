#pragma once

#include <imgui.h>
#include "imgui_functions.h"

#include "../units/units.hpp"
#include "../transformation/transformation.hpp"

namespace render::imgui {

    template<template<typename> typename Origin>
    class Context {
        using Vector2Ori = Magnum::Math::Vector2<Origin<float>>;
    public:
        explicit Context(ImDrawList &dl, int lodLevel = 0) : _drawList{dl}, _lod{lodLevel} {
        }

        void drawCircle(Vector2Ori center, Origin<float> radius, ImU32 color, math::Pixels thickness) {
            auto rpx = _transformation.transformMagnitude(radius);
            auto centerpx = _transformation.transformPoint(center);
            imgui::drawCircle(_drawList, centerpx, rpx, color, (float) thickness);
        }

        void drawLine(Vector2Ori ini, Vector2Ori end, ImU32 color, math::Pixels thickness) {
            auto iniPoint = _transformation.transformPoint(ini);
            auto endPoint = _transformation.transformPoint(end);
            imgui::drawLine(_drawList, iniPoint, endPoint, color, thickness);
        }

    protected:
        ImDrawList &_drawList;
        int _lod = 0;
        math::xy::types::Transformation<Origin, math::types::PixelsT, float> _transformation;
    };
}
#pragma once

#include <Magnum/Math/Vector2.h>
#include <Magnum/Magnum.h>
#include "../units/units.hpp"

#define IM_VEC2_CLASS_EXTRA                                                \
        ImVec2(const Magnum::Vector2& f) { x = f.x(); y = f.y(); }         \
        operator Magnum::Vector2() const { return Magnum::Vector2(x,y); }  \
                                                                           \
        ImVec2(const Magnum::Math::Vector2<math::Pixels>& f) { x = (float)f.x(); y = (float)f.y(); }         \
        operator Magnum::Math::Vector2<math::Pixels>() const { return Magnum::Math::Vector2{math::Pixels{x}, math::Pixels{y}}; }

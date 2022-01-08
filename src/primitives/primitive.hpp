#pragma once

#include "math/units.h"
#include "render.h"

namespace madbricks::render {

    struct Primitive {
        virtual void doRender(RenderContext<math::MilimetersT, float> &render) const = 0;
    };

    struct LineElement : Primitive {
        [[nodiscard]] virtual std::vector<Magnum::Math::Vector2<math::Milimeters>> getPolyline() const = 0;
    };
}
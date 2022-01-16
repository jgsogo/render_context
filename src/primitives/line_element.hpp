#pragma once

#include <vector>
#include "primitive.hpp"

namespace primitives {

    struct LineElement : Primitive {
        [[nodiscard]] virtual std::vector<Vector2Mm> getPolyline() const = 0;
    };
}
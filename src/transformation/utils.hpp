#pragma once

#include "transformation.hpp"

namespace math::xy::types {
    /* Some useful precooked transformations */

    /* Get a matrix that rotates inputs around a fixed point given in the arguments */
    template<const char *symbol, typename T>
    constexpr Transformation<symbol, symbol, T> rotationWithCenter(const typename Transformation<symbol, symbol, T>::Rotation &angle,
                                                                   const typename Transformation<symbol, symbol, T>::Translation &center) {
        Transformation<symbol, symbol, T> t{center};
        Transformation<symbol, symbol, T> r{angle};
        return t * r / t;
    }

    /* Get a matrix that scales inputs with a fixed point given in arguments (homothetic) */
    template<const char *symbolOrigin, const char *symbolTarget, typename T>
    constexpr Transformation<symbolOrigin, symbolTarget, T> scaleWithCenter(const typename Transformation<symbolOrigin, symbolTarget, T>::Scale &scale,
                                                                            const Magnum::Math::Vector2<typename Transformation<symbolOrigin, symbolTarget, T>::OriginUnits> &center) {
        using TargetUnits = typename Transformation<symbolOrigin, symbolTarget, T>::TargetUnits;
        auto centerAsTarget = Magnum::Math::Vector2{TargetUnits{static_cast<float>(center.x())}, TargetUnits{static_cast<float>(center.y())}};
        auto targetCenter = scale * center;
        return Transformation<symbolOrigin, symbolTarget, T>{scale, centerAsTarget - targetCenter};
    }
}


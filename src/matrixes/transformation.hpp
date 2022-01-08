#pragma once

#include <ostream>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Math/Vector2.h>
#include "units/ratio.hpp"

namespace math::xy::types {
    /* Simplification of homogeneous coordinate matrices. Here translation is
     * performed after rotation and scaling, thus it is expressed in Target coordinates */

    namespace _impl {
        template<template<typename> typename Origin,
                template<typename> typename Target,
                typename T>
        class BaseTransformation {
        public:
            using Translation = Magnum::Math::Vector2<Target<T>>;
            using Rotation = Magnum::Math::Deg<T>;
            using Scale = ::math::types::RatioT<Origin, Target, T>;

            BaseTransformation() = default;

            BaseTransformation(const Translation &t, const Rotation &r) : _translation(t), _rotation(r) {}

            Magnum::Math::Vector2<Target<T>> transformPoint(const Magnum::Math::Vector2<Origin<T>> &in) const {
                auto translatetyped = Magnum::Math::Vector2<T>{in};
                return Magnum::Math::Vector2<Target<T>>{_transformation.transformPoint(translatetyped)};
            }

        protected:
            void update(const Translation &translate,
                        const Rotation &rotate,
                        const Scale &scale) {  // Always preserve x/y ratio
                auto translatetyped = Magnum::Math::Vector2<T>{translate};
                auto scaletyped = Magnum::Math::Vector2<T>{static_cast<T>(scale), static_cast<T>(scale)};
                _transformation = Magnum::Math::Matrix3<T>::translation(translatetyped) *
                                  Magnum::Math::Matrix3<T>::rotation(rotate) *
                                  Magnum::Math::Matrix3<T>::scaling(scaletyped);
            }

            void update(const Translation &translate,
                        const Rotation &rotate) {
                auto translatetyped = Magnum::Math::Vector2<T>{translate};
                _transformation = Magnum::Math::Matrix3<T>::translation(translatetyped) *
                                  Magnum::Math::Matrix3<T>::rotation(rotate);
            }

        protected:
            Translation _translation;
            Rotation _rotation;
            Magnum::Math::Matrix3<T> _transformation;
        };
    }

    template<template<typename> typename Origin,
            template<typename> typename Target,
            typename T, typename Enable = void>
    class Transformation : public _impl::BaseTransformation<Origin, Target, T> {
    public:
        using Translation = typename _impl::BaseTransformation<Origin, Target, T>::Translation;
        using Rotation = typename _impl::BaseTransformation<Origin, Target, T>::Rotation;
        using Scale = typename _impl::BaseTransformation<Origin, Target, T>::Scale;

        Transformation() = default;

        Transformation(const Translation &t, const Scale &s, const Rotation &r)
                : _impl::BaseTransformation<Origin, Target, T>(t, r), _scale(s) {
            this->update(_impl::BaseTransformation<Origin, Target, T>::_translation, _impl::BaseTransformation<Origin, Target, T>::_rotation, _scale);
        }

        friend std::ostream &operator<<(std::ostream &os, const Transformation &tf) {
            os << "[" << Origin<T>::symbol << " > " << Target<T>::symbol << "]";
            os << " scale(" << tf._scale << "),";
            os << " rotate(" << static_cast<T>(tf._rotation) << "),";
            os << " translate(" << tf._translation.x() << ", " << tf._translation.y() << ")";
            return os;
        }

        /*
        // Set translation, it is expressed in target coordinates
        void setTranslate(const Magnum::Math::Vector2<Target<T>> &translate) {
            transformation.setTranslate(Magnum::Vector2{translate});
        }

        void setScale(Origin<T> oriMagnitude, Target<T> targetMagnitude) {
            auto ratio = targetMagnitude / oriMagnitude;
            this->setScale(ratio);
        }

        void setScale(const Ratio <Origin, Target> &ratio) {
            transformation.setScale((float) ratio);
        }

        void setRotate(const Magnum::Deg &angle) {
            transformation.setRotate(angle);
        }
        */
    protected:
        Scale _scale = Scale{Magnum::Math::IdentityInit};
    };

    template<template<typename> typename Origin,
            template<typename> typename Target,
            typename T>
    class Transformation<Origin, Target, T, typename std::enable_if_t<std::is_same_v<Origin<T>, Target<T>>>>
            : public _impl::BaseTransformation<Origin, Target, T> {
    public:
        using Translation = typename _impl::BaseTransformation<Origin, Target, T>::Translation;
        using Rotation = typename _impl::BaseTransformation<Origin, Target, T>::Rotation;

        Transformation() = default;

        Transformation(const Translation &t, const Rotation &r) : _impl::BaseTransformation<Origin, Target, T>(t, r) {
            this->update(_impl::BaseTransformation<Origin, Target, T>::_translation, _impl::BaseTransformation<Origin, Target, T>::_rotation);
        }

        friend std::ostream &operator<<(std::ostream &os, const Transformation &tf) {
            os << "[" << Origin<T>::symbol << " > " << Target<T>::symbol << "]";
            os << " rotate(" << static_cast<T>(tf._rotation) << "),";
            os << " translate(" << tf._translation.x() << ", " << tf._translation.y() << ")";
            return os;
        }

    };

}

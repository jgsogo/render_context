#pragma once

#include <ostream>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Math/Vector2.h>
#include "../units/ratio.hpp"

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
            using Scale = typename std::conditional<!std::is_same_v<Origin<T>, Target<T>>, ::math::types::RatioT<Origin, Target, T>, Magnum::NoInitT>::type;

            BaseTransformation() = default;

            BaseTransformation(const Translation &t, const Rotation &r) : _translation(t), _rotation(r) {}

            Magnum::Math::Vector2<Target<T>> transformPoint(const Magnum::Math::Vector2<Origin<T>> &in) const {
                auto translatetyped = Magnum::Math::Vector2<T>{in};
                return Magnum::Math::Vector2<Target<T>>{_transformation.transformPoint(translatetyped)};
            }

            /* Transform magnitude taking only scale into account */
            Target<T> transformMagnitude(const Origin<T> &in) {
                return Target<T>{static_cast<T>(in) * _transformation.uniformScaling()};
            }

            /* Functions to set/update transformation */
            void set(const Translation &translate) {
                this->_set(translate);
                this->_update();
            }

            void set(const Rotation &rotation) {
                this->_set(rotation);
                this->_update();
            }

            template<typename Arg1, typename... Args>
            void set(const Arg1 &t, const Args &... args) {
                this->_set(t, args...);
                this->_update();
            };

        protected:
            virtual void _update() = 0;

            virtual void _set(const Scale &) {};

            void _set(const Translation &translate) {
                _translation = translate;
            }

            void _set(const Rotation &rotation) {
                _rotation = rotation;
            }

            template<typename Arg1, typename... Args>
            void _set(const Arg1 &t, const Args &... args) {
                this->_set(t);
                this->_set(args...);
            };

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
        using _impl::BaseTransformation<Origin, Target, T>::set;
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

        void set(const Scale &scale) {
            this->_set(scale);
            this->_update();
        }

    protected:
        void _set(const Scale &scale) override {
            _scale = scale;
        }

        void _update() override {
            this->update(_impl::BaseTransformation<Origin, Target, T>::_translation, _impl::BaseTransformation<Origin, Target, T>::_rotation, _scale);
        }

        template<template<typename> typename OriginT,
                template<typename> typename TargetT,
                template<typename> typename FinalT,
                typename TT>
        friend Transformation<OriginT, FinalT, TT> operator*(const Transformation<TargetT, FinalT, TT> &lhs, const Transformation<OriginT, TargetT, TT> &rhs);

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
        using _impl::BaseTransformation<Origin, Target, T>::_transformation;

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

    protected:
        void _update() override {
            this->update(_impl::BaseTransformation<Origin, Target, T>::_translation, _impl::BaseTransformation<Origin, Target, T>::_rotation);
        }
    };


    template<template<typename> typename Origin,
            template<typename> typename Target,
            template<typename> typename Final,
            typename T>
    Transformation<Origin, Final, T> operator*(const Transformation<Target, Final, T> &lhs, const Transformation<Origin, Target, T> &rhs) {
        Magnum::Math::Matrix3<T> mResult = lhs._transformation * rhs._transformation;
        auto translate = Magnum::Math::Vector2<Final<T>>{mResult.translation()};
        auto rotation = Magnum::Rad{mResult.rotation()[0][0]};
        if constexpr(std::is_same_v<Origin<T>, Final<T>>) {
            return Transformation<Origin, Final, T>{translate, rotation};
        } else {
            auto scale = ::math::types::RatioT<Origin, Final, T>{Origin<T>{1}, Final<T>{mResult.uniformScaling()}};
            return Transformation<Origin, Final, T>{translate, scale, rotation};
        }
    }

    /*
    template<template<typename> typename Origin,
            template<typename> typename Target,
            template<typename> typename Final,
            typename T>
    Transformation2D<Origin, Final, T> operator/(const Transformation2D<Target, Final, T> &lhs, const Transformation2D<Target, Origin, T> &rhs) {
        Magnum::Math::Matrix3<T> matrix{lhs.getMatrix() * rhs.getMatrix().inverted()};
        return Transformation2D<Origin, Final, T>{matrix};
    }
    */
}

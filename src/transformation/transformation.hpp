#pragma once

#include <ostream>
#include <cassert>
#include <Magnum/Magnum.h>
#include <Magnum/Math/Matrix3.h>
#include <Magnum/Math/Vector2.h>
#include <Magnum/Math/Complex.h>
#include "../units/ratio.hpp"

namespace math::xy::types {
    /* Simplification of homogeneous coordinate matrices. Here translation is
     * performed after rotation and scaling, thus it is expressed in Target coordinates */

    namespace _impl {
        template<const char *symbolOrigin, const char *symbolTarget, typename T>
        class BaseTransformation {
        public:
            using OriginUnits = ::math::types::NamedUnitT<T, symbolOrigin>;
            using TargetUnits = ::math::types::NamedUnitT<T, symbolTarget>;

            using Translation = Magnum::Math::Vector2<TargetUnits>;
            using Rotation = Magnum::Math::Deg<T>;
            using Scale = typename std::conditional<!std::is_same_v<OriginUnits, TargetUnits>, ::math::types::RatioT<symbolOrigin, symbolTarget, T>, Magnum::NoInitT>::type;

            BaseTransformation() = default;

            BaseTransformation(const Translation &t, const Rotation &r) : _translation(t), _rotation(r) {}

            Magnum::Math::Vector2<TargetUnits> transformPoint(const Magnum::Math::Vector2<OriginUnits> &in) const {
                auto translatetyped = Magnum::Math::Vector2<T>{in};
                return Magnum::Math::Vector2<TargetUnits>{_transformation.transformPoint(translatetyped)};
            }

            Magnum::Math::Vector2<OriginUnits> transformInverse(const Magnum::Math::Vector2<TargetUnits> &in) const {
                auto translatetyped = Magnum::Math::Vector2<T>{in};
                // TODO: We don´t want to compute inverted every time
                return Magnum::Math::Vector2<OriginUnits>{_transformation.inverted().transformPoint(translatetyped)};
            }

            /* Transform magnitude taking only scale into account */
            TargetUnits transformMagnitude(const OriginUnits &in) const {
                return TargetUnits{static_cast<T>(in) * _transformation.uniformScaling()};
            }

            OriginUnits transfromInverseMagnitude(const TargetUnits &in) const {
                return OriginUnits{static_cast<T>(in) / _transformation.uniformScaling()};
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

            const Translation &getTranslation() const {
                return _translation;
            }

            const Rotation &getRotation() const {
                return _rotation;
            }

            void translate(const Translation &tr) {
                this->set(_translation + tr);
            }

            void rotate(const Rotation &r) {
                this->set(_rotation + r);
            }

            void rotate(const Rotation &r,
                        const Magnum::Math::Vector2<OriginUnits> &rotateCenter) {
                Magnum::Matrix3 itt =
                        _transformation *
                        Magnum::Matrix3::translation(-rotateCenter) *
                        Magnum::Matrix3::rotation(r) *
                        Magnum::Matrix3::translation(rotateCenter);
                auto translate = itt.translation();
                auto rotate = Magnum::Complex::fromMatrix(itt.rotation()).normalized().angle();
                auto scale = itt.uniformScaling();
                this->set(rotate, scale, translate);
            }

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

    template<const char *symbolOrigin, const char *symbolTarget, typename T, typename Enable = void>
    class Transformation : public _impl::BaseTransformation<symbolOrigin, symbolTarget, T> {
    public:
        using OriginUnits = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::OriginUnits;
        using _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::set;
        using Translation = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::Translation;
        using Rotation = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::Rotation;
        using Scale = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::Scale;

        Transformation() = default;

        template<typename Arg1, typename... Args>
        Transformation(const Arg1 &t, const Args &... args) {
            this->set(t, args...);
        }

        friend std::ostream &operator<<(std::ostream &os, const Transformation &tf) {
            os << "[" << symbolOrigin << " > " << symbolTarget << "]";
            os << " scale(" << tf._scale << "),";
            os << " rotate(" << static_cast<T>(tf._rotation) << "),";
            os << " translate(" << tf._translation.x() << ", " << tf._translation.y() << ")";
            return os;
        }

        void set(const Scale &scale) {
            this->_set(scale);
            this->_update();
        }

        const Scale &getScale() const {
            return _scale;
        }

        void scale(const Scale &s) {

        }

        void scale(const Scale &s, const Magnum::Math::Vector2<OriginUnits> &scaleCenter_) {

        }

    protected:
        void _set(const Scale &scale) override {
            _scale = scale;
        }

        void _update() override {
            this->update(_impl::BaseTransformation<symbolOrigin, symbolTarget, T>::_translation,
                         _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::_rotation, _scale);
        }

        template<const char *OriginT,
                const char *TargetT,
                const char *FinalT,
                typename TT>
        friend Transformation<OriginT, FinalT, TT> operator*(const Transformation<TargetT, FinalT, TT> &lhs, const Transformation<OriginT, TargetT, TT> &rhs);

    protected:
        Scale _scale = Scale{Magnum::Math::IdentityInit};
    };

    template<const char *symbolOrigin, const char *symbolTarget, typename T>
    class Transformation<symbolOrigin, symbolTarget, T, typename std::enable_if_t<std::is_same_v<math::types::NamedUnitT<T, symbolOrigin>, math::types::NamedUnitT<T, symbolTarget >>>>
            : public _impl::BaseTransformation<symbolOrigin, symbolTarget, T> {
    public:
        using Translation = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::Translation;
        using Rotation = typename _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::Rotation;
        using _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::_transformation;

        Transformation() = default;

        template<typename Arg1, typename... Args>
        Transformation(const Arg1 &t, const Args &... args) {
            this->set(t, args...);
        }

        friend std::ostream &operator<<(std::ostream &os, const Transformation &tf) {
            os << "[" << symbolOrigin << " > " << symbolTarget << "]";
            os << " rotate(" << static_cast<T>(tf._rotation) << "),";
            os << " translate(" << tf._translation.x() << ", " << tf._translation.y() << ")";
            return os;
        }

    protected:
        void _update() override {
            this->update(_impl::BaseTransformation<symbolOrigin, symbolTarget, T>::_translation,
                         _impl::BaseTransformation<symbolOrigin, symbolTarget, T>::_rotation);
        }
    };


    template<const char *Origin,
            const char *Target,
            const char *Final,
            typename T>
    Transformation<Origin, Final, T> operator*(const Transformation<Target, Final, T> &lhs, const Transformation<Origin, Target, T> &rhs) {
        Magnum::Math::Matrix3<T> mResult = lhs._transformation * rhs._transformation;
        typename Transformation<Origin, Final, T>::Translation translate = Magnum::Math::Vector2<math::types::NamedUnitT<T, Final>>{mResult.translation()};
        typename Transformation<Origin, Final, T>::Rotation rotation = Magnum::Complex::fromMatrix(mResult.rotation()).normalized().angle();
        auto scaleFactor = mResult.uniformScaling();
        if constexpr(std::is_same_v<math::types::NamedUnitT<T, Origin>, math::types::NamedUnitT<T, Final>>) {
            assert(scaleFactor == 1.f); // "Scale factor between same units should be equal to one (no scale)";
            return Transformation<Origin, Final, T>{translate, rotation};
        } else {
            auto scale = ::math::types::RatioT<Origin, Final, T>{math::types::NamedUnitT<T, Origin>{1}, math::types::NamedUnitT<T, Final>{scaleFactor}};
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

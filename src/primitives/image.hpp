#pragma once

#include "../units/named_unit.hpp"
#include "primitive.hpp"

namespace primitives {

    struct TextureImage {
        // Contains a reference to the texture, but also the UV coordinates for the specific image inside it
        explicit TextureImage(Magnum::GL::Texture2D &textureID) : textureID{textureID} {}

        Magnum::Math::Range2D<render::UVCoordinates> uvCoordinates;
        Magnum::GL::Texture2D &textureID;
    };

    template<const char *Origin, typename TDrawList>
    struct Image : Primitive<Origin, TDrawList> {
        using RenderContext = typename Primitive<Origin, TDrawList>::RenderContext;
        using OriginUnits = typename RenderContext::OriginUnits;
        using Vector2Ori = typename RenderContext::Vector2Ori;

        explicit Image(Magnum::GL::Texture2D &textureID) : texture{textureID} {}

        TextureImage texture;
        Magnum::Math::Range2D<OriginUnits> bbox;

        void doRender(RenderContext &render) const override {
            render.drawImage(texture.textureID, texture.uvCoordinates, bbox);
        }
    };

}

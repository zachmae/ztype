/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ISprite
*/

#ifndef PAML_ISPRITE_HPP
    #define PAML_ISPRITE_HPP

    #include "IDrawable.hpp"
    #include "ITransformable.hpp"

    #include "ITexture.hpp"
    #include "IColor.hpp"

namespace paml {

    class ISprite : public IDrawable, public ITransformable {

        public:

            virtual ~ISprite() = default;

            virtual void setTexture(const ITexture &texture) = 0;
            virtual ITexture &getTexture() const = 0;

            virtual void setColor(IColor &color) = 0;
            virtual IColor &getColor() const = 0;

    };
}

#endif // !PAML_ISPRITE_HPP

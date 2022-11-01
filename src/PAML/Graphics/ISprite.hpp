/*
** EPITECH PROJECT, 2021
** xxx
** File description:
** xxx
*/

#ifndef PAML_ISPRITE_HPP
#define PAML_ISPRITE_HPP

#include "../Graphics.hpp"

namespace paml {

    class ISprite : public IDrawable, public ITransformable {

        virtual void setTexture(const ITexture &texture) = 0;
        virtual ITexture &getTexture() const = 0;
        virtual void setColor(IColor &color) = 0;
        virtual IColor &getColor() const = 0;

    };
}

#endif // !PAML_ISPRITE_HPP

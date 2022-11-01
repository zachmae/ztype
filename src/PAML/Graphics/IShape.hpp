/*
** EPITECH PROJECT, 2021
** xxx
** File description:
** xxx
*/

#ifndef PAML_ISHAPE_HPP
#define PAML_ISHAPE_HPP

#include "../Graphics.hpp"

namespace paml {

    class IShape : public IDrawable, public ITransformable {

        virtual void setTexture(const ITexture &texture) = 0;
        virtual ITexture &getTexture() const = 0;
        virtual void setColor(IColor &color) = 0;
        virtual IColor &getColor() const = 0;

    };
}

#endif // !PAML_ISHAPE_HPP

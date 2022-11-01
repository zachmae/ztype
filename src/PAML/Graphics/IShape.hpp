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

        // TODO - Change return types and entry parameters
        virtual void setTexture() = 0;
        virtual void getTexture() = 0;
        virtual void setColor() = 0;
        virtual void getColor() = 0;

        virtual void setPosition() = 0;
        virtual void getPosition() = 0;
        virtual void setRotation() = 0;
        virtual void getRotation() = 0;
        virtual void setScale() = 0;
        virtual void getScale() = 0;

        virtual void move() = 0;
        virtual void rotate() = 0;
        virtual void scale() = 0;
    };
}

#endif // !PAML_ISHAPE_HPP

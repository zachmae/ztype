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

        // TODO - Change return types and entry parameters
        virtual void setTexture() = 0;
        virtual void getTexture() = 0;
        virtual void setColor() = 0;
        virtual void getColor() = 0;



    };
}

#endif // !PAML_ISPRITE_HPP

/*
** EPITECH PROJECT, 2021
** IText
** File description:
** IText
*/

#ifndef PAML_IDRAWABLE_HPP
#define PAML_IDRAWABLE_HPP

#include "../Graphics.hpp"

namespace paml {

    class ITransformable {

        // Setters & Getters
        virtual void setPosition() = 0;
        virtual void getPosition() = 0;
        virtual void setRotation() = 0;
        virtual float getRotation() = 0;
        virtual std::pair<float, float> setScale() = 0;
        virtual void getScale() = 0;


        // Actions
        virtual void move() = 0;
        virtual void rotate() = 0;
        virtual void scale() = 0;

    };

}

#endif // !PAML_IDRAWABLE_HPP

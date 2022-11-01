/*
** EPITECH PROJECT, 2021
** IText
** File description:
** IText
*/

#ifndef PAML_ITRANSFORMABLE_HPP
#define PAML_ITRANSFORMABLE_HPP

#include "../Graphics.hpp"

namespace paml {

    class ITransformable {

        // Setters & Getters
        virtual void setPosition(std::pair<float, float>) = 0;
        virtual std::pair<float, float> getPosition() const = 0;
        virtual void setRotation(float angle) = 0;
        virtual float getRotation() const = 0;
        virtual void setScale(std::pair<float, float>) = 0;
        virtual std::pair<float, float> getScale() const = 0;


        // Actions
        virtual void move(std::pair<float, float>) = 0;
        virtual void rotate(float angle) = 0;
        virtual void scale(std::pair<float, float>) = 0;

    };

}

#endif // !PAML_ITRANSFORMABLE_HPP

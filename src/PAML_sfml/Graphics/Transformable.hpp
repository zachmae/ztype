/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ITransformable
*/

#ifndef PAML_SFML_TRANSFORMABLE_HPP
    #define PAML_SFML_TRANSFORMABLE_HPP

    #include <SFML/Graphics.hpp>

    #include "../../PAML/Graphics/ITransformable.hpp"

    #include "../System/Vector2.hpp"

namespace paml_sfml {

    class Transformable : public paml::ITransformable {

        public:

            virtual ~Transformable() = default;

            // Setters & Getters
            virtual void setPosition(IVector2<float>) = 0;
            virtual IVector2<float> getPosition() const = 0;

            virtual void setRotation(float angle) = 0;
            virtual float getRotation() const = 0;

            virtual void setScale(IVector2<float>) = 0;
            virtual IVector2<float> getScale() const = 0;

            //Actions
            virtual void move(IVector2<float>) = 0;
            virtual void rotate(float angle) = 0;
            virtual void scale(IVector2<float>) = 0;

    };

}

#endif // !PAML_ITRANSFORMABLE_HPP

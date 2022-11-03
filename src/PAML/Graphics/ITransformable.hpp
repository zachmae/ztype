/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ITransformable
*/

#ifndef PAML_ITRANSFORMABLE_HPP
    #define PAML_ITRANSFORMABLE_HPP

    #include "../System/IVector2.hpp"

namespace paml {

    class ITransformable {

        public:

            virtual ~ITransformable() = default;

            // Setters & Getters
            virtual void setPosition(IVector2<float>) = 0;
            virtual IVector2<float> getPosition() const = 0;

            virtual void setRotation(float angle) = 0;
            virtual float getRotation() const = 0;

            virtual void setScale(IVector2<float>) = 0;
            virtual IVector2<float> getScale() const = 0;

            // Actions
            virtual void move(IVector2<float>) = 0;
            virtual void rotate(float angle) = 0;
            virtual void scale(IVector2<float>) = 0;

    };

}

#endif // !PAML_ITRANSFORMABLE_HPP

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IShape
*/

#ifndef PAML_ISHAPE_HPP
    #define PAML_ISHAPE_HPP

    #include "IDrawable.hpp"
    #include "ITransformable.hpp"

    #include "ITexture.hpp"
    #include "IColor.hpp"

namespace paml {

    class IShape : public IDrawable, public ITransformable {

        public:

            virtual ~IShape() = default;

            virtual void setTexture(const ITexture &texture) = 0;
            virtual ITexture &getTexture() const = 0;

            virtual void setColor(IColor &color) = 0;
            virtual IColor &getColor() const = 0;

    };

}

#endif // !PAML_ISHAPE_HPP

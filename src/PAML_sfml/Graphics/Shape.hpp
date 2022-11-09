/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IShape
*/

#ifndef PAML_SFML_SHAPE_HPP
    #define PAML_SFML_SHAPE_HPP

    #include <SFML/Graphics.hpp>

    #include "../../PAML/Graphics.hpp"
    #include "Texture.hpp"
    #include "Color.hpp"

    #include "Texture.hpp"
    #include "Color.hpp"

namespace paml_sfml {

    class Shape : public paml::IShape, public paml::Drawable, public paml::Transformable {

        public:

            ~IShape() = default;

            void setTexture(const Texture &texture) = 0;
            Texture &getTexture() const = 0;

            void setColor(Color &color) = 0;
            Color &getColor() const = 0;

        private:

            sf::Shape _shape;


    };

}

#endif // !PAML_SFML_ISHAPE_HPP

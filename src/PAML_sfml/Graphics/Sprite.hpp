/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Sprite
*/

#ifndef PAML_SFML_SPRITE_HPP
    #define PAML_SFML_SPRITE_HPP

    #include <SFML/Graphics.hpp>

    #include "../../PAML/Graphics.hpp"

    #include "Drawable.hpp"
    #include "Transformable.hpp"
    #include "Texture.hpp"
    #include "Color.hpp"

namespace paml_sfml {

    class Sprite : public paml::ISprite, public Drawable, public Transformable {

        public:

            ~ISprite() = default;

            void setTexture(const Texture &texture) = 0;
            Texture &getTexture() const = 0;

            void setColor(Color &color) = 0;
            Color &getColor() const = 0;

        private:

            sf::Sprite _sprite;
    };
}

#endif // !PAML_ISPRITE_HPP

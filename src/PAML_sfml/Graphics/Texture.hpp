/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Texture
*/

#ifndef PAML_SFML_TEXTURE_HPP
    #define PAML_SFML_TEXTURE_HPP

    #include <string>
    #include <SFML/Graphics.hpp>

    #include "../System/Type.hpp"


namespace paml_sfml {

    class Texture : public ITexture {

        public:

            Texture()
            : _texture()
            {
                ;
            }

            Texture(const Texture &copy)
            : _texture(copy._texture)
            {
            }

            ~Texture() = default;

            bool loadFromFile(const std::string &filename)
            {
                _texture.loadFromFile(filename);
            }

        friend class Sprite;

        private:

            sf::Texture _texture;
    };

}

#endif // !PAML_SFML_TEXTURE_HPP

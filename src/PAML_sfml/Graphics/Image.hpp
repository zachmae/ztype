/*
** EPITECH PROJECT, 2021
** IColor
** File description:
** Image
*/

#ifndef PAML_SFML_IMAGE_HPP
    #define PAML_SFML_IMAGE_HPP

    #include <string>

    #include "../../PAML/Graphics.hpp"

    #include "../System/Type.hpp"

namespace paml_sfml {

    class Image : public paml::IImage  {

        public:

            Image();
            ~Image() = default;

            void create(uint32_t width, uint32_t height, const IColor &color);

            bool loadFromFile(const std::string &filename);
            bool saveToFile(const std::string &filename) const;

            void setPixel(uint32_t posX, uint32_t posY, IColor &color);

            IColor &getColor(uint32_t posX, uint32_t posY) const;

        private:

            sf::Image _image;
    };

}

#endif // !PAML__SFML_IMAGE_HPP

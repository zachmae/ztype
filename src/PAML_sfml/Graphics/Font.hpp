/*
** EPITECH PROJECT, 2021
** IText
** File description:
** Font
*/

#ifndef PAML_SFML_FONT_HPP
    #define PAML_SFML_FONT_HPP

    #include <string>

    #include "../../PAML/Graphics.hpp"

namespace paml_sfml {

    class Font : public paml::IFont {

        public:

            ~Font() = default;
            bool loadFromFile(const std::string &filename) = 0;
            bool saveToFile(const std::string &filename) const = 0;

    };

}

#endif // !PAML_SFML_FONT_HPP

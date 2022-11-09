/*
** EPITECH PROJECT, 2021
** IColor
** File description:
** Color
*/

#ifndef PAML_SFML_COLOR_HPP
    #define PAML_SFML_COLOR_HPP

    #include "../../PAML/Graphics.hpp"

    #include "../System/Type.hpp"

namespace paml_sfml {

    class Color : public paml::IColor {

        public:

            ~Color() = default;

            uint32_t toInteger() const;

    };

}

#endif // !PAML_SFML_ICOLOR_HPP

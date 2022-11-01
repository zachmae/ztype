/*
** EPITECH PROJECT, 2021
** IText
** File description:
** IText
*/

#ifndef PAML_ITEXTURE_HPP
#define PAML_ITEXTURE_HPP

#include "../Graphics.hpp"

namespace paml {

    class ITexture {

        virtual void create(uint32_t width, uint32_t height) = 0;

        // TODO - Not sure about this one
        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual void update(ITexture &Texture) = 0;

    };

}

#endif // !PAML_ITEXTURE_HPP

/*
** EPITECH PROJECT, 2021
** IColor
** File description:
** IColor
*/

#ifndef PAML_IIMAGE_HPP_
#define PAML_IIMAGE_HPP_

#include "../Graphics.hpp"

namespace paml {

    class IImage  {

        virtual void create(uint32_t width, uint32_t height, const IColor &color) = 0;

        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual bool saveToFile(const std::string &filename) const = 0;

        virtual void setPixel(uint32_t posX, uint32_t posY, IColor &color) = 0;
        virtual IColor &getColor(uint32_t posX, uint32_t posY) const = 0;

    };

}

#endif // !PAML_IIMAGE_HPP_

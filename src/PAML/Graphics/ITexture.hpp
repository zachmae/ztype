/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ITexture
*/

#ifndef PAML_ITEXTURE_HPP
    #define PAML_ITEXTURE_HPP

    #include "../System/Type.hpp"
    #include <string>

namespace paml {

    class ITexture {

        public:

            virtual ~ITexture() = default;
            virtual bool loadFromFile(const std::string &filename) = 0;

            // TODO - Not sure about this one
            virtual bool create(uint32_t width, uint32_t height) = 0;
            virtual void update(ITexture &Texture) = 0;

    };

}

#endif // !PAML_ITEXTURE_HPP

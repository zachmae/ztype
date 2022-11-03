/*
** EPITECH PROJECT, 2021
** IColor
** File description:
** IColor
*/

#ifndef PAML_ICOLOR_HPP_
#define PAML_ICOLOR_HPP_

#include "../System/Type.hpp"

namespace paml {

    class IColor {

        public:

        // TODO - Change types for draw method
            virtual uint32_t toInteger() const = 0;

    };

}

#endif // !PAML_ICOLOR_HPP_

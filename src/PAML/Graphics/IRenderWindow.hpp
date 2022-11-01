/*
** EPITECH PROJECT, 2021
** IColor
** File description:
** IColor
*/

#ifndef PAML_IRENDERWINDOW_HPP_
#define PAML_IRENDERWINDOW_HPP_

#include "../Graphics.hpp"

namespace paml {

    class IRenderWindow {

        virtual void clear() = 0;
        virtual void draw() = 0;

    };

}

#endif // !PAML_IRENDERWINDOW_HPP_

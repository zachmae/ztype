/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IRenderWindow
*/

#ifndef PAML_IRENDERWINDOW_HPP_
    #define PAML_IRENDERWINDOW_HPP_

    #include "IRenderTarget.hpp"
    #include "../Window/IWindow.hpp"

namespace paml {

    class IRenderWindow : public IRenderTarget, public IWindow {

        public:

            virtual ~IRenderWindow() = default;

            //Nothing cause everything is on parent
    };

}

#endif // !PAML_IRENDERWINDOW_HPP_

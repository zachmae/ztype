/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IMouse
*/

#ifndef PAML_SFML_MOUSE_HPP
#define PAML_SFML_IMOUSE_HPP

#include "../../PAML/Window.hpp"

#include "../System/Vector2.hpp"
#include "../System/Type.hpp"

#include "Window.hpp"

namespace paml_sfml {

    class Mouse : public IMouse {

    public:
        enum Button
        {
            Left,
            Right,
            Middle,
            XButton1,
            XButton2,

            ButtonCount
        };

        enum Wheel
        {
            VerticalWheel,
            HorizontalWheel
        };

        Mouse()
        {}

        ~Mouse() = default;

        bool isButtonPressed(Button button)
        {
            _mouse.isButtonPressed(static_cast<sf::Mouse::Button>(button));
        }

        IVector2<int32_t> getPosition();
        void setPosition(const Vector2<int32_t> &position);

        IVector2<int32_t> getPosition(const Window &relativeTo);
        void setPosition(const IVector2<int32_t> &position, const Window &relativeTo);

        sf::Mouse _mouse;
    };

} // namespace paml

#endif /* !IMOUSE_HPP_ */

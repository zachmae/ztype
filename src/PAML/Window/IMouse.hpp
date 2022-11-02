/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IMouse
*/

#ifndef IMOUSE_HPP
    #define IMOUSE_HPP

    #include "../System/IVector2.hpp"
    #include "../System/Type.hpp"
    #include "IWindow.hpp"

namespace paml {

class IMouse {

    public:

        enum Button {
            Left,
            Right,
            Middle,
            XButton1,
            XButton2,

            ButtonCount
        };

        enum Wheel {
            VerticalWheel,
            HorizontalWheel
        };

        virtual bool isButtonPressed(Button button);

        virtual IVector2<int32_t> getPosition();

        virtual IVector2<int32_t> getPosition(const IWindow & relativeTo);

        virtual void setPosition(const IVector2<int32_t>& position);

        virtual void setPosition(const IVector2<int32_t>& position, const IWindow & relativeTo);
};

} // namespace paml

#endif /* !IMOUSE_HPP_ */

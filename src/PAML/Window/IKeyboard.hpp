/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IKeyboard
*/

#ifndef IKEYBOARD_HPP_
#define IKEYBOARD_HPP_

namespace paml {

    class IKeyboard {

        public:

            enum Key {
                Unknown = -1,
                A = 0,
                B,
                C,
                D,
                E,
                F,
                G,
                H,
                I,
                J,
                K,
                L,
                M,
                N,
                O,
                P,
                Q,
                R,
                S,
                T,
                U,
                V,
                W,
                X,
                Y,
                Z,
                Num0,
                Num1,
                Num2,
                Num3,
                Num4,
                Num5,
                Num6,
                Num7,
                Num8,
                Num9,
                Escape,
                LControl,
                LShift,
                LAlt,
                LSystem,
                RControl,
                RShift,
                RAlt,
                RSystem,
                Menu,
                LBracket,
                RBracket,
                Semicolon,
                Comma,
                Period,
                Quote,
                Slash,
                Backslash,
                Tilde,
                Equal,
                Hyphen,
                Space,
                Enter,
                Backspace,
                Tab,
                PageUp,
                PageDown,
                End,
                Home,
                Insert,
                Delete,
                Add,
                Subtract,
                Multiply,
                Divide,
                Left,
                Right,
                Up,
                Down,
                Numpad0,
                Numpad1,
                Numpad2,
                Numpad3,
                Numpad4,
                Numpad5,
                Numpad6,
                Numpad7,
                Numpad8,
                Numpad9,
                F1,
                F2,
                F3,
                F4,
                F5,
                F6,
                F7,
                F8,
                F9,
                F10,
                F11,
                F12,
                F13,
                F14,
                F15,
                Pause,

                KeyCount,

                // Deprecated values:
                Dash      = Hyphen,
                BackSpace = Backspace,
                BackSlash = Backslash,
                SemiColon = Semicolon,
                Return    = Enter
            };

            virtual bool isKeyPressed(Key key) = 0;

            virtual void setVirtualKeyboardVisible(bool visible) = 0;

    };

} // namespace paml

#endif /* !IKEYBOARD_HPP_ */

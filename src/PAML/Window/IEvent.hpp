/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IEvent
*/

#ifndef PAML_IEVENT_HPP_
    #define PAML_IEVENT_HPP_

    #include "IKeyboard.hpp"
    #include "IMouse.hpp"
    #include "../System/Type.hpp"

namespace paml
{

    class IEvent {

        public:

            virtual ~IEvent() = default;

            virtual bool isClosed(); //The window requested to be closed (no data)

            virtual bool isResized(); //The window was resized (data in event.size)
            virtual IVector2<uint32_t> GetSize();

            virtual bool isLostFocus(); //The window lost the focus (no data)

            virtual bool GainedFocus(); //The window gained the focus (no data)

            virtual bool isTextEntered(); //A character was entered (data in event.text)
            virtual uint32_t GetUnicode(); // UTF-32 Unicode value of the character.

            virtual bool isKeyPressed(); //A key was pressed (data in event.key)
            virtual bool isKeyReleased(); //A key was released (data in event.key)
            virtual IKeyboard::Key GetKey(); //Code of the key that has been pressed//release.

            virtual bool isMouseWheelScrolled(); //The mouse wheel was scrolled (data in event.mouseWheelScroll)
            virtual float GetMouseWheelScroll(); //mouse wheel scroll value

            virtual bool isMouseButtonPressed();//A mouse button was pressed (data in event.mouseButton)
            virtual bool isMouseButtonReleased(); //A mouse button was released (data in event.mouseButton)
            virtual IMouse::Button GetMouseButton(); //Code of the button that has been pressed//release.

            virtual bool isMouseMoved(); //The mouse cursor moved (data in event.mouseMove)
            virtual IVector2<int32_t> GetMousePosition(); // position of the mouse pointer, relative to the owner window.

            virtual bool isMouseEntered(); //The mouse cursor entered the area of the window (no data)

            virtual bool isMouseLeft(); //The mouse cursor left the area of the window (no data)

    };

} // namespace paml


#endif /* !PAML_IEVENT_HPP_ */

/* test 1

            //Window
            virtual bool isResized();

            virtual bool isClosed();

            virtual bool LostFocus();
            virtual bool GainedFocus();

            //Keyboard
            virtual bool IsKeyPressed(IKeyboard::Key key); // Check if a key has been pressed once
            virtual bool IsKeyDown(IKeyboard::Key key); // Check if a key is being pressed
            virtual bool IsKeyReleased(IKeyboard::Key key); // Check if a key has been released once
            virtual bool IsKeyUp(IKeyboard::Key key); // Check if a key is NOT being pressed

            virtual bool isTextEntered(); //A character was entered (data in event.text)
            virtual uint32_t GetUnicode(); // UTF-32 Unicode value of the character.

            //Mouse
            virtual bool IsMouseButtonPressed(); // Check if a mouse button has been pressed once
            virtual bool IsMouseButtonReleased(); // Check if a mouse button has been released once

            virtual int32_t GetMouseButton();

            virtual bool isMouseMoved(); //The mouse cursor moved

            virtual bool IsMouseEntered(); // Check if a mouse button is NOT being pressed
            virtual bool IsMouseLeft(); // Check if a mouse button is NOT being pressed

            virtual bool isMouseWheelScrolled(); // Number of ticks the wheel has moved (positive is up, negative is down)

            virtual float GetMouseWheelScroll(); // Number of ticks the wheel has moved (positive is up, negative is down)

/* test 2

            struct SizeEvent
            {
                unsigned int width;
                unsigned int height;
            };

            struct KeyEvent
            {
                IKeyboard::Key code;
                bool          alt;
                bool          control;
                bool          shift;
                bool          system;
            };

            struct TextEvent
            {
                uint32_t unicode;
            };

            struct MouseMoveEvent
            {
                int x;
                int y;
            };

            struct MouseButtonEvent
            {
                IMouse::Button button;
                int           x;
                int           y;
            };

            struct MouseWheelScrollEvent
            {
                IMouse::Wheel wheel;
                float        delta;
                int          x;
                int          y;
            };

            enum EventType
            {
                Closed,
                Resized,
                LostFocus,
                GainedFocus,
                TextEntered,
                KeyPressed,
                KeyReleased,
                MouseWheelMoved,
                MouseWheelScrolled,
                MouseButtonPressed,
                MouseButtonReleased,
                MouseMoved,
                MouseEntered,
                MouseLeft,
                JoystickButtonPressed,
                JoystickButtonReleased,
                JoystickMoved,
                JoystickConnected,
                JoystickDisconnected,
                TouchBegan,
                TouchMoved,
                TouchEnded,
                SensorChanged,

                Count
            };

     // Member data
     EventType type;

            union {
                SizeEvent             size;
                KeyEvent              key;
                TextEvent             text;
                MouseMoveEvent        mouseMove;
                MouseButtonEvent      mouseButton;
                MouseWheelEvent       mouseWheel;
                MouseWheelScrollEvent mouseWheelScroll;
            }

*/
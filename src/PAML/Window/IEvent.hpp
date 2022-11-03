/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IEvent
*/

#ifndef PAML_IEVENT_HPP_
    #define PAML_IEVENT_HPP_

    #include "../System/Type.hpp"

    #include "IKeyboard.hpp"
    #include "IMouse.hpp"


namespace paml {

    class IEvent {

        public:

            virtual ~IEvent() = default;

            virtual bool isClosed() = 0; //The window requested to be closed (no data)

            virtual bool isResized() = 0; //The window was resized (data in event.size)
            virtual IVector2<uint32_t> GetSize() = 0;

            virtual bool isLostFocus() = 0; //The window lost the focus (no data)

            virtual bool GainedFocus() = 0; //The window gained the focus (no data)

            virtual bool isTextEntered() = 0; //A character was entered (data in event.text)
            virtual uint32_t GetUnicode() = 0; // UTF-32 Unicode value of the character.

            virtual bool isKeyPressed() = 0; //A key was pressed (data in event.key)
            virtual bool isKeyReleased() = 0; //A key was released (data in event.key)
            virtual IKeyboard::Key GetKey() = 0; //Code of the key that has been pressed//release.

            virtual bool isMouseWheelScrolled() = 0; //The mouse wheel was scrolled (data in event.mouseWheelScroll)
            virtual float GetMouseWheelScroll() = 0; //mouse wheel scroll value

            virtual bool isMouseButtonPressed() = 0;//A mouse button was pressed (data in event.mouseButton)
            virtual bool isMouseButtonReleased() = 0; //A mouse button was released (data in event.mouseButton)
            virtual IMouse::Button GetMouseButton() = 0; //Code of the button that has been pressed//release.

            virtual bool isMouseMoved() = 0; //The mouse cursor moved (data in event.mouseMove)
            virtual IVector2<int32_t> GetMousePosition() = 0; // position of the mouse pointer, relative to the owner window.

            virtual bool isMouseEntered(); //The mouse cursor entered the area of the window (no data)

            virtual bool isMouseLeft(); //The mouse cursor left the area of the window (no data)

    };

} // namespace paml


#endif /* !PAML_IEVENT_HPP_ */
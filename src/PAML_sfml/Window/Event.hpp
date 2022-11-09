/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IEvent
*/

#ifndef PAML_SFML_EVENT_HPP_
    #define PAML_SFML_EVENT_HPP_

    #include "../System/Type.hpp"
    #include "../System/Vector2.hpp"

    #include "Keyboard.hpp"
    #include "Mouse.hpp"


namespace paml_sfml {

    class Event : public paml::IEvent {

        public:

            Event();
            ~Event() = default;

            bool isClosed();

            bool isResized();
            Vector2<uint32_t> GetSize();

            bool isLostFocus();
            bool GainedFocus();

            bool isTextEntered();
            uint32_t GetUnicode();

            bool isKeyPressed();
            bool isKeyReleased();
            Keyboard::Key GetKey();

            bool isMouseWheelScrolled();
            float GetMouseWheelScroll();

            bool isMouseButtonPressed();
            bool isMouseButtonReleased();
            Mouse::Button GetMouseButton();

            bool isMouseMoved();
            Vector2<int32_t> GetMousePosition();

            bool isMouseEntered();
            bool isMouseLeft();

    };

} // namespace paml


#endif /* !PAML_IEVENT_HPP_ */
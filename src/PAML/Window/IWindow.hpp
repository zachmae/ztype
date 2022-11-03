/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Window
*/

#ifndef PAML_IWINDOW_HPP
    #define PAML_IWINDOW_HPP

    #include "../System/IVector2.hpp"
    #include "../System/Type.hpp"
    #include "../System/INonCopiable.hpp"
    #include "../Graphics/IDrawable.hpp" //sprite should inherit from there
    #include "IEvent.hpp"

namespace paml {

    class IWindow : public INonCopyable {

        public:

            enum style
            {
                None       = 0,
                Titlebar   = 1 << 0,
                Resize     = 1 << 1,
                Close      = 1 << 2,
                Fullscreen = 1 << 3,

                Default = Titlebar | Resize | Close
            };

            virtual ~IWindow() = default;
            virtual bool close() = 0;
            virtual bool isOpen() const = 0;
            virtual void clear() = 0;
            virtual void display() = 0;
            virtual void setFrameLimit(uint32_t) = 0;
            virtual void setMouseCursorVisible(bool) = 0;
            virtual void setVisible(bool) = 0;
            virtual IVector2<uint32_t> getSize() const = 0;
            virtual void setSize(const IVector2<uint32_t> &) = 0;
            virtual void draw(IDrawable &) = 0;
            virtual void pollEvent(IEvent &) = 0;
    };

} // namespace paml

#endif /* !WINDOW_HPP_ */

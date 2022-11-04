/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Window
*/

#ifndef PAML_SFML_WINDOW_HPP
    #define PAML_SFML_WINDOW_HPP

    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>

    #include "../../PAML/Window/IWindow.hpp" //sprite should inherit from there
    #include "../../PAML/System.hpp" //sprite should inherit from there

    #include "../System/Vector2.hpp"

namespace paml_sfml {

    class Window : public paml::IWindow {

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

            Window(sf::VideoMode mode, const std::string& title)
            : _window(mode, title)
            {

            }

            ~Window();

            bool close()
            {
                _window.close();
            }
            bool isOpen()
            {}

            void display()
            {
                _window.display();
            }

            void setFramerateLimit(uint32_t limit)
            {
                _window.setFramerateLimit(limit);
            }

            void setMouseCursorVisible(bool visible)
            {
                _window.setMouseCursorVisible(visible);
            }

            void setVisible(bool visible)
            {
                _window.setVisible(visible);
            }

            IVector2<uint32_t> getSize() const
            {
                return _window.getSize();
            }
            void setSize(const IVector2<uint32_t> &v)
            {
                _window.setSize(static_cast<Vector2<uint32_t> &>(v));
            }

            void draw(Drawable &drawable)
            {
                _window.draw(drawable);
            }

            void pollEvent(Event &e)
            {
                _window.pollEvent(e);
            }

            Vector2<float> mapPixelToCoords (const Vector2<int32_t> &point) const {
                _window.mapPixelToCoords(point);
            }
        private:
            sf::RenderWindow _window;
    };

} // namespace paml

#endif /* !PAML_SFML_WINDOW_HPP */

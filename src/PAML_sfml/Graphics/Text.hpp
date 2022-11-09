/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Text
*/

#ifndef PAML_SFML_TEXT_HPP
    #define PAML_SFML_TEXT_HPP

    //lib externe
    #include <string>
    #include <SFML/Graphics.hpp>

    //Paml_SFML
    #include "../../PAML/Graphics.hpp"

    //PAML_SFML
    #include "../System.hpp"
    #include "../Window.hpp"

    #include "Drawable.hpp"
    #include "Transformable.hpp"
    #include "Font.hpp"
    #include "Color.hpp"

namespace paml_sfml {

    class Text : public IText, public Drawable, public Transformable {

        public:

            ~IText() = default;

            void setString(const std::string &string) = 0;
            std::string &getString() const = 0;

            void setFont(const IFont &font) = 0;
            Font &getFont() const = 0;

            void setCharacterSize(uint32_t size) = 0;
            uint32_t getCharacterSize() const = 0;

            void setLineSpacing(float spacing) = 0;
            float getLineSpacing() const = 0;

            void setLetterSpacing(float spacing) = 0;
            float getLetterSpacing() const = 0;

            void setColor(const Color &color) = 0;
            Color &getColor() const = 0;

            friend class Window;

        private:
            sf::Text text;
    };

}

#endif // !PAML_ITEXT_HPP

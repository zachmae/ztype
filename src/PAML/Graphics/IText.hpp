/*
** EPITECH PROJECT, 2021
** IText
** File description:
** IText
*/

#ifndef PAML_ITEXT_HPP
#define PAML_ITEXT_HPP

#include "../Graphics.hpp"

namespace paml {

    class IText : public IDrawable, public ITransformable {

        virtual void setString(const std::string &string) = 0;
        virtual std::string &getString() const = 0;

        virtual void setFont(const IFont &font) = 0;
        virtual IFont &getFont() const = 0;

        virtual void setCharacterSize(uint32_t size) = 0;
        virtual uint32_t getCharacterSize() const = 0;

        virtual void setLineSpacing(float spacing) = 0;
        virtual float getLineSpacing() const = 0;

        virtual void setLetterSpacing(float spacing) = 0;
        virtual float getLetterSpacing() const = 0;

        virtual void setColor(const IColor &color) = 0;
        virtual IColor &getColor() const = 0;

    };

}

#endif // !PAML_ITEXT_HPP

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IText
*/

#ifndef PAML_ITEXT_HPP
    #define PAML_ITEXT_HPP

    #include "../System/Type.hpp"

    #include "../Graphics/IDrawable.hpp"
    #include "../Graphics/ITransformable.hpp"

    #include "../Graphics/IFont.hpp"
    #include "../Graphics/IColor.hpp"

namespace paml {

    class IText : public IDrawable, public ITransformable {

        public:

            virtual ~IText() = default;

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

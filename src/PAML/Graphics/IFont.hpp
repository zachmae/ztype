/*
** EPITECH PROJECT, 2021
** IText
** File description:
** IText
*/

#ifndef PAML_IFONT_HPP
    #define PAML_IFONT_HPP

    #include <string>

namespace paml {

    class IFont {

        public:

            virtual ~IFont() = default;
            virtual bool loadFromFile(const std::string &filename) = 0;
            virtual bool saveToFile(const std::string &filename) const = 0;

    };

}

#endif // !PAML_IFONT_HPP

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IVector2
*/

#ifndef PAML_SFML_VECTOR2_HPP
    #define PAML_SFML_VECTOR2_HPP

    #include "../../PAML/System.hpp"
    #include <SFML/System.hpp>

namespace paml_sfml {

    template <typename T>
    class Vector2 : public paml::IVector2 {

        public:

            T x;
            T y;

            //paml_sfml to sf
            Vector2(const sf::Vector2<T> &value) {
                return static_cast<Vector2<T>>(value);
            }

            Vector2<T> operator=(sf::Vector2<T> &value) {
                return static_cast<Vector2<T>>(value);
            }

            //sf to paml_sfml
            sf::Vector2(const Vector2<T> &value) {
                return static_cast<sf::Vector2<T>>(value);
            }

            sf::Vector2<T> operator=(Vector2<T> &value) {
                return static_cast<sf::Vector2<T>>(value);
            }

    };

} // namespace paml

#endif /* !PAML_SFML_VECTOR2_HPP_ */

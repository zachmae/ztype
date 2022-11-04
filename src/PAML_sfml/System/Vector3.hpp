/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IVector3
*/

#ifndef PAML_SFML_VECTOR3_HPP
    #define PAML_SFML_VECTOR3_HPP

    #include "../../PAML/System.hpp"
    #include <SFML/System/Vector3.hpp>

namespace paml_sfml {

    template <typename T>
    class Vector3 : public IVector3 {

        public:
            T x;
            T y;
            T z;

            Vector3<T>(const sf::Vector3<T> &value) {
                return static_cast<Vector3<T>>(value);
            }
            Vector3<T> operator =(sf::Vector3<T> &value) {
                return static_cast<Vector3<T>>(value);
            }

            //sf to paml_sfml
            sf::Vector3(const Vector3<T> &value) {
                return static_cast<sf::Vector3<T>>(value);
            }

            sf::Vector3<T> operator=(Vector3<T> &value) {
                return static_cast<sf::Vector3<T>>(value);
            }

    };

} // namespace paml

#endif /* !PAML_SFML_VECTOR3_HPP_ */

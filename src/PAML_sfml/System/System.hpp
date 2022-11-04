/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ISystem
*/

#ifndef PAML_SFML_SYSTEM_HPP
    #define PAML_SFML_SYSTEM_HPP

    #include <SFML/System.hpp>

    #include "../../PAML/System.hpp"

    #include "Time.hpp"

namespace paml_sfml {

    class System : public paml::ISystem {

        public:

            void sleep(Time time)
            {
                sf::sleep(time._time);
            }

    };

} // namespace paml

#endif /* !PAML_SFML_SYSTEM_HPP_ */

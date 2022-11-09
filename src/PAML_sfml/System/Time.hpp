/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ITime
*/


#ifndef PAML_SFML_TIME_HPP
    #define PAML_SFML_TIME_HPP

    #include <SFML/System.hpp>

    #include "../../PAML/System.hpp"

namespace paml_sfml {

    class Time : public paml::ITime {

        public:

            Time() : _time()
            {
            }

            Time(Time &&t)
            : _time(t._time)
            {
            }

            Time(const sf::Time &t)
            : _time(t)
            {
            }

            ~Time() = default;

            float asSeconds()
            {
                return _time.asSeconds();
            }
            paml::int32_t asMilliseconds()
            {
                return _time.asMilliseconds();
            }
            paml::int64_t asMicroseconds()
            {
                return _time.asMicroseconds();
            }

            friend class System;

        private:
            sf::Time _time;
    };

} // namespace paml

#endif /* !PAML_SFML_ITIME_HPP_ */

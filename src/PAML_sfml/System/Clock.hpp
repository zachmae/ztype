/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IClock
*/

#ifndef PAML_SFML_CLOCK_HPP
    #define PAML_SFML_CLOCK_HPP

    #include <SFML/System.hpp>

    #include "../../PAML/System/IClock.hpp"

    #include "Time.hpp"

namespace paml_sfml {

    class Clock : public paml::IClock {

        public:
            Clock()
            : _clock()
            {
            }

            Clock(sf::Clock &&clock)
            : _clock(clock)
            {
            }

            Clock(const sf::Clock &clock)
            : _clock(clock)
            {
            }

            ~Clock()
            {
            }

            Time getElapsedTime()
            {
                return _clock.getElapsedTime();
            }

            Time restart()
            {
                return _clock.restart();
            }

        private:
            sf::Clock _clock;
    };

} // namespace paml

#endif /* !ICLOCK_HPP_ */

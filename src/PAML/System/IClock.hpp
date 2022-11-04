/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IClock
*/

#ifndef PAML_ICLOCK_HPP
    #define PAML_ICLOCK_HPP

    #include "ITime.hpp"

namespace paml {

    class IClock {

        public:
            virtual ~IClock() = default;

            virtual ITime getElapsedTime() = 0;
            virtual ITime restart() = 0;

    };

} // namespace paml

#endif /* !PAML_ICLOCK_HPP_ */

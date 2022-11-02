/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** IClock
*/

#ifndef ICLOCK_HPP
    #define ICLOCK_HPP

    #include "ITime.hpp"

namespace paml
{

class IClock {

    public:
        virtual ~IClock() = default;
        virtual ITime getElapsedTime () = 0;
        virtual ITime restart () = 0;

};

} // namespace paml

#endif /* !ICLOCK_HPP_ */

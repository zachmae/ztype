/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ITime
*/


#ifndef ITIME_HPP
    #define ITIME_HPP

    #include "Type.hpp"

namespace paml
{

class ITime {

    public:
        virtual ~ITime() = default;
        virtual float asSeconds() = 0;
        virtual int32_t asMilliseconds() = 0;
        virtual int64_t asMicroseconds() = 0;
};

} // namespace paml

#endif /* !ITIME_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ISystem
*/

#ifndef PAML_ISYSTEM_HPP
    #define PAML_ISYSTEM_HPP

    #include "ITime.hpp"

namespace paml
{

class ISystem
{

    public:
        virtual void sleep(ITime time) = 0;

};

} // namespace paml

#endif /* !ISYSTEM_HPP_ */

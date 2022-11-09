/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** INonCopyable
*/

#ifndef PAML_SFML_NONCOPYABLE_HPP
    #define PAML_SFML_NONCOPYABLE_HPP

    #include "../../PAML/System.hpp"

namespace paml_sfml {

    class NonCopyable : public paml::INonCopyable {

        protected:

            NonCopyable();
            NonCopyable(const NonCopyable &) = delete;
            virtual NonCopyable & operator=(const NonCopyable &) = delete;

    };

} // namespace paml

#endif /* !PAML_SFML_NONCOPYABLE_HPP */

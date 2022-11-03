/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** INonCopyable
*/

#ifndef PAML_INONCOPyABLE_HPP
#define PAML_INONCOPyABLE_HPP

namespace paml {

class INonCopyable {

    protected:

        virtual ~INonCopyable() = default;

    private:

//        virtual INonCopyable(const INonCopyable &) = 0;
        virtual INonCopyable& operator =(const INonCopyable &) = 0;

};

} // namespace paml

#endif /* !PAML_INONCOPIABLE_HPP */

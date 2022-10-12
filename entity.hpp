/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

    #include <cstddef>

    class entity
    {
        public:
            //Constructors
            entity();
            explicit entity(size_t x);

            //Destructors
            ~entity();

            // Setters
            void setSize(size_t size) { _size = size; }

            // Getters
            size_t getSize() const { return _size; }

            // Operations
            operator size_t() const { return _size; };

        protected:
            size_t _size;

        private:
    };

#endif /* !ENTITY_HPP_ */

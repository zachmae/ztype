/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include "entity.hpp"
#include "sparse_array.hpp"
#include <iostream>

int main()
{
    entity e;
    size_t size;

    std::cout << e.getSize() << std::endl;
    e.setSize(42);
    std::cout << e.getSize() << std::endl;
    size = e;
    std::cout << size << std::endl;
}
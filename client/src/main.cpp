/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** main
*/

#include <iostream>
#include "client.hpp"

static int displayUsage(int ret_value)
{
    std::cout << "USAGE: ./rtype ip port\n\n" \
        "\tip\tis the server ip adress on which to the server listens" \
        "\tport\tis the port number on which the server socket listens\n"
              << std::endl;
    return ret_value;
}

static bool isNumber(const std::string &str)
{
    if (str.empty())
        return false;
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

int main(int ac, char const * const av[])
{
    if (ac == 2 && av[1] != nullptr && (std::string(av[1]) == "-h" ||
                                        std::string(av[1]) == "--help"))
        return displayUsage(0);
    if (ac != 3)
        return displayUsage(84);
    if (!isNumber(av[2]))
        return std::cerr << "Error : Port must be a number" << std::endl, 84;
    return client(av[1], static_cast<unsigned short>(std::stoi(av[2])));
}
/*
** EPITECH PROJECT, 2022
** main.cpp
** File description:
** main
*/

#include <iostream>
#include "server.hpp"

static int display_usage(int ret_value)
{
    std::cout << "USAGE: ./myteams_server port\n\n"
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
    if (ac != 2 || av[1] == nullptr)
        return display_usage(84);
    if (av[1] != nullptr && (std::string(av[1]) == "-h" ||
                             std::string(av[1]) == "--help"))
        return display_usage(0);
    if (!isNumber(av[1]))
        return std::cerr << "Port must be a number" << std::endl, 84;
    return server(static_cast<unsigned short>(std::stoi(av[1])));
}

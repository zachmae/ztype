/*
** EPITECH PROJECT, 2022
** rtype
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** main_client
*/

#include <SFML/Window.hpp>
#include <cctype>
#include "ProjectManager/ProjectManager.hpp"
#include "main_server.hpp"

/**
 * @brief Display Usage if the user has question on how to launch the executable
 *
 * @param ret_value : Return value of the program
 * @return int : Return value of the program that has been passed in parameter
 */
static int displayUsage(int ret_value)
{
    std::cout << "USAGE: ./rtype [ip] port\n\n" \
        "\tIf ip is not provided, the server will be launched\n" \
        "\tip\tis the server ip adress on which to the server listens" \
        "\tport\tis the port number on which the server socket listens\n"
              << std::endl;
    return ret_value;
}

/**
 * @brief Check if the string is a number
 *
 * @param str
 * @return true
 * @return false
 */
static bool isNumber(const std::string &str)
{
    if (str.empty())
        return false;
    std::string::const_iterator i = str.begin();
    while (i != str.end() && std::isdigit(*i)) ++i;
    return !str.empty() && i == str.end();
}

/**
 * @brief Main function of the client
 *
 * @param ac
 * @param av
 * @return int
 */
int main(int ac, char const * const av[])
{
    if (ac == 2)
        server::StartServer(static_cast<unsigned short>(std::atoi(av[1])));
    if (ac < 2 || ac > 3)
        return displayUsage(84);
    if (ac == 2 && av[1] != nullptr && (std::string(av[1]) == "-h" ||
                                        std::string(av[1]) == "--help"))
        return displayUsage(0);

    if (!isNumber(av[2]))
        return std::cerr << "Error : Port must be a number" << std::endl, 84;

    srand(static_cast<unsigned int>(time(nullptr)));
    Project::ProjectManager pm("../assets/conf/project-manager.json");
    return pm.Start(av[1], static_cast<unsigned short>(std::atoi(av[2])));

}
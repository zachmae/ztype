/*
** EPITECH PROJECT, 2022
** rtype
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** main_client
*/

#include <cctype>
#include "UserClient/ClientProjectManager.hpp"
#include "main_server.hpp"
#include "Languages.hpp"

/**
 * @brief Display Usage if the user has question on how to launch the executable
 *
 * @param ret_value : Return value of the program
 * @return int : Return value of the program that has been passed in parameter
 */
static int displayUsage(int ret_value)
{
    std::cout << "USAGE: ./rtype [ip] port -l lang -d diff --debug\n\n" \
        "\tIf ip is not provided, the server will be launched\n" \
        "\tip\tis the server ip adress on which to the server listens" \
        "\tport\tis the port number on which the server socket listens\n" \
        "\t--debug\tto activate the debug mode\n" \
        "\t-d\tto choose a difficulty level (going from 1 to 4)\n" \
        "\t-l\tis the language in which the game will be displayed see assets/lang/load.json to check the languages" << std::endl;
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

static void handle_flags(int ac, char const * const av[])
{
    for (int i = 1; i < ac; i++) {
        if (std::string(av[i]) == "--debug")
            Globals::debug_mode = true;
        if (std::string(av[i]) == "-d")
            if (i + 1 < ac && isNumber(av[i + 1]) && std::stoi(av[i + 1]) >= 0 && std::stoi(av[i + 1]) <= 4)
                    Globals::difficulty = std::stoi(av[i + 1]);
    }
}

/**
 * @brief Main function of the client
 *
 * @param ac : arguments of the main (number of arguments)
 * @param av : arguments of the main (arguments)
 * @return int
 */
int main(int ac, char const * const av[])
{
    prepare_language(ac, av);
    display_dict();
    if (ac < 2)
        return displayUsage(84);
    if (ac == 2 && av[1] != nullptr && (std::string(av[1]) == "-h" ||
                                        std::string(av[1]) == "--help"))
        return displayUsage(0);
    if (ac == 2)
        server::StartServer(static_cast<unsigned short>(std::atoi(av[1])));
    if (!isNumber(av[2]))
        return std::cerr << "Error : Port must be a number" << std::endl, 84;

    srand(static_cast<unsigned int>(time(nullptr)));
    handle_flags(ac, av);
    User::ClientProjectManager upm("../assets/conf/project-manager.json");
    return upm.Start(av[1], static_cast<unsigned short>(std::atoi(av[2])));

}
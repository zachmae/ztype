/*
** EPITECH PROJECT, 2022
** rtype
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** main_server
*/

#include <SFML/Network.hpp>
#include <cctype>
#include <iostream>
#include <string>
#include "./Network/Server.hpp"
#include "./Network/Server.hpp"


/**
 * @brief Display Usage if the user has question on how to launch the executable
 *
 * @param ret_value : Return value of the program
 * @return int : Return value of the program that has been passed in parameter
 */
/*
static int displayUsage(int ret_value)
{
    std::cout << "USAGE: ./rtype [ip] port\n\n" \
        "\tIf ip is not provided, the server will be launched\n" \
        "\tip\tis the server ip adress on which to the server listens" \
        "\tport\tis the port number on which the server socket listens\n"
              << std::endl;
    return ret_value;
}

static bool isNumber(const std::string &str)
{
    if (str.empty())
        return false;
    std::string::const_iterator i = str.begin();
    while (i != str.end() && std::isdigit(*i)) ++i;
    return !str.empty() && i == str.end();
}
*/
namespace server {

    /**
     * @brief Server
     *
     * @param ip
     * @param port
     * @return int
     */
    int StartServer(unsigned short port)
    {
        Server server(port);
        sf::TcpSocket *socket;
        sf::Packet sfp;
        std::string compare;
        ;
        while (1) {
            if (server.selectorWait()) {
                if (server.isNewConnection()) {
                    std::cout << "New Client" << std::endl;
                    server.accept();
                }
                socket = server.isNewMessage();
                if (socket != nullptr) {
                    sfp = server.receive(socket);
                    ;
                    if (sfp.getData() != NULL) {
                        sfp >> compare;
                        if (compare == "pos_client") {
                            int id = 0;
                            float x = 0;
                            float y = 0;
                            ;
                            sfp >> id >> x >> y;
                            int i = 0;
                            for (auto &client : server.getClients()) {
                                if (i != id) {
                                    sf::Packet newSfp;
                                    ;
                                    newSfp << "client_pos" << id << x << y;
                                    client->send(newSfp);
                                }
                                ++i;
                            }
                        }
                    }
                }
            }
        }
        return 0;
    };

} //namespace server
/*
int main(int ac, char const * const av[])
{
    std::cout << "Server started" << std::endl;
    if (ac != 2)
        return displayUsage(84);
    if (ac == 2 && av[1] != nullptr && (std::string(av[1]) == "-h" ||
                                        std::string(av[1]) == "--help"))
        return displayUsage(0);
    if (!isNumber(av[1]))
        return std::cerr << "Error : Port must be a number" << std::endl, 84;
    return server::StartServer(static_cast<unsigned short>(std::atoi(av[1])));
}
*/
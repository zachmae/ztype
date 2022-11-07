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
 * @namespace server
 *
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

}
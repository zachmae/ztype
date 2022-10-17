/*
** EPITECH PROJECT, 2022
** client.hpp
** File description:
** client
*/



#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <SFML/Network.hpp>

typedef struct client_s {
    sf::TcpSocket socket;
    int id{};
    int x{};
    int y{};
} client_t;

class Server {
public:
    /**
     * @brief Construct a new Server by bind the listener to a port
     *
     * @param port unsigned short
     */
    inline explicit Server(unsigned short port) {
        if (_listener.listen(port) != sf::Socket::Status::Done) // Bind the listener to a port
            std::cerr << "Error : Fail to bind the port" << std::endl;
        _selector.add(_listener);
        _id = 0;
    };

    /**
     * @brief Destroy the Server by destroying all client and \
     *        removing the listener and closing it
     */
    inline ~Server() {
        for (auto &client : _clients)
            delete client;
        _selector.remove(_listener);
        _listener.close();
    };

    /**
     * @brief Accept a new client
     */
    void accept();

    /**
     * @brief Send a message to all clients
     * @param message
     */
    void send(std::string const &message);

    /**
     * @brief Send a position to all clients
     * @param x position x of the player
     * @param y position y of the player
     */
    void sendPos(float x, float y);

    /**
     * @brief Receive a message from a client
     * @param client socket of the client
     * @return sf::Packet
     */
    sf::Packet receive(sf::TcpSocket *client);

    /**
     * @brief Check if there is a new client
     * @return bool (true if there is a new client)
     */
    bool isNewConnection() { return _selector.isReady(_listener); };

    /**
     * @brief Check if there is a new message from a client
     * @return sf::TcpSocket* (null if there is no new message)
     */
    sf::TcpSocket *isNewMessage() {
        for (auto &client : _clients) {
            if (_selector.isReady(*client)) {
                return client;
            }
        }
        return nullptr;
    };


    bool selectorWait() { return _selector.wait(sf::microseconds(1)); };

    std::vector<sf::TcpSocket *>  getClients() { return _clients; };

private:
    sf::TcpSocket _socket;                                   // Create a socket
    sf::SocketSelector _selector;                            // Create a selector
    sf::TcpListener _listener;                               // Create a listener
    std::vector<sf::TcpSocket *> _clients;                   // Create a vector of clients
    int _id;                                                 // Create an id for each client
};

#endif /* SERVER_HPP_ */
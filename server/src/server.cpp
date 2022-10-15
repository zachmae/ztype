/*
** EPITECH PROJECT, 2022
** server.cpp
** File description:
** server
*/

#include <iostream>
#include <SFML/Network.hpp>
#include <vector>
#include <csignal>

void exit_server() // exit server when you ctrl + c
{
    std::cout << "\b\bClosing server !\n" << std::endl;
    exit(0);
}

[[noreturn]] int server(unsigned short port)
{
    sf::TcpSocket socket;                                   // Create a socket
    sf::TcpListener listener;                               // Create a listener
    sf::Socket::Status status = listener.listen(port);      // Bind the listener to a port
    sf::SocketSelector selector;                            // Create a selector
    std::vector<sf::TcpSocket *> clients;                   // Create a vector of clients


    std::signal(SIGINT, (__sighandler_t)exit_server);   // Catch ctrl + c
    selector.add(listener);                                     // Add the listener to the selector
    if (status != sf::Socket::Status::Done) {                      // Check if the binding has succeeded
        std::cerr << "Error : Connection failed" << std::endl;     // Display an error message
        exit(84);                                            // Exit with error
    }
    while (true) {
        if (selector.wait())
        {
            if (selector.isReady(listener)) {
                auto *client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Status::Done) {
                    selector.add(*client);
                    clients.push_back(client);
                }
                sf::Packet receivePacket;
                if (client->receive(receivePacket) == sf::Socket::Status::Done) {
                    std::string receiveMessage;
                    receivePacket >> receiveMessage;
                    std::cout << "Client \"" << receiveMessage << "\" connected" << std::endl;
                }
            } else {
                for (auto &client : clients) {
                    int x = 0;
                    int y = 0;
                    if (selector.isReady(*client)) {
                        sf::Packet receivePacket;
                        if (client->receive(receivePacket) == sf::Socket::Status::Done) {
                            std::string receiveMessage;
                            receivePacket >> x;
                            receivePacket >> y;
                            receivePacket >> receiveMessage;
                            std::cout << receiveMessage << "x:" << x << "y :" << y << std::endl;
                        }
                    }
                }
            }
        }
    }
            /*if (selector.isReady(listener)) {                                                            // The listener is ready: there is a pending connection

                auto *client = new sf::TcpSocket();                                                         // Create a new TCP socket
                if (listener.accept(*client) == sf::Socket::Status::Done) {                                      // Accept the new connection
                    clients.push_back(client);                                                              // Add the new client to the clients list
                    selector.add(*client);                                                               // Add the new client to the selector so that we will

                    sf::Packet packet;                                                                      // Create a packet to send a message to the new client
                    packet << "Welcome to the chat !";                                                      // Fill the packet
                    if (client->send(packet) != sf::Socket::Status::Done) {                                                                 // Send it to the new client
                        std::cerr << "Error : Sending failed" << std::endl;                                  // Display a message
                    }
                    if (client->receive(packet) == sf::Socket::Status::Done) {                                       // Receive a message from the client
                        std::string message;                                                                    // Extract the message from the packet
                        packet >> message;                                                                      // Display the message
                        std::cout << "Message received: " << message;
                    }
                }
            }
            } else {
                std::cout << "boucle inf" << std::endl;
                for (auto &client : clients) {                                                          // Loop through all clients
                    if (selector.isReady(*client)) {                                                             // If the client has sent some data, we can receive it

                        sf::Packet packet;                                                                          // Create a packet to receive the message

                        if (client->receive(packet) == sf::Socket::Status::Done) {                                       // Receive a message from the client
                            std::string message;                                                                    // Extract the message from the packet
                            packet >> message;                                                                      // Display the message
                            std::cout << "Message received: " << message;                                           // Send a message to the client

                            sf::Packet sendPacket;                                                                  // Create a packet to send a message to the client
                            sendPacket << "Hello from server";                                                      // Append the message to the packet
                        }
                    }
                }
            }
        }*/
}

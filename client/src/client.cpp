/*
** EPITECH PROJECT, 2022
** client.cpp
** File description:
** client
*/

#include <iostream>
#include <SFML/Network.hpp>

int client(std::string const &ip, unsigned short port)
{
    sf::TcpSocket socket;
    std::optional<sf::IpAddress> address = sf::IpAddress::resolve(ip);
    sf::Socket::Status status = socket.connect(address.value(), port, sf::seconds(15));
    std::string name;
    std::string message;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    while ( name.empty()) {
        std::cerr << "Need a name" << std::endl;
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    }

    if (status != sf::Socket::Status::Done) {
        std::cerr << "Error : Connection failed" << std::endl;
        return 84;
    } else {
        std::cout << "Connected to " << ip << ":" << port << std::endl;
        sf::Packet sendPacket;
        sendPacket << name;
        if (socket.send(sendPacket) == sf::Socket::Status::Done) {
            std::cout << "Message sent" << std::endl;
        } else {
            std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
            return 84;
        }
        /*sf::Packet receivePacket;
        std::cout << "trying" << std::endl;
        if (socket.receive(receivePacket) == sf::Socket::Status::Done) {
            std::cout << "Message received" << std::endl;
            std::string receiveMessage;
            receivePacket >> receiveMessage;
            std::cout << receiveMessage << std::endl;
        } else {
            std::cerr << "Error : Receiving failed (maybe server down)" << std::endl;
            return 84;
        }*/
    }
    int x = 0;
    int y = 0;
    while (message != "exit") {
        message.clear();
        sf::Packet sendPacket;
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);
        sendPacket << x << y << message;
        sendPacket << x << y << message;
        socket.send(sendPacket);
        if (socket.send(sendPacket) == sf::Socket::Status::Done) {
            std::cout << "Message sent" << std::endl;
        } else {
            std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
            return 84;
        }
        x++;
        y += 2;
    }
    return 0;
}
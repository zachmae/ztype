/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

Client::Client(std::string const &ip, unsigned short port)
{
    sf::Packet packet;

    if (_socket.connect(ip, port, sf::seconds(15)) != sf::Socket::Status::Done) {
        std::cerr << "Error : Connection failed" << std::endl;
        exit(84);
    }
    receive() >> _id;
}

void Client::send(std::string const &message)
{
    sf::Packet packet;

    packet << message << _id << 0 << message;
    if (_socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
        exit(84);
    }
}

void Client::sendPos(float x, float y)
{
    sf::Packet packet;

    packet << "pos" << _id << x << y;
    if (_socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
        exit(84);
    }
}

void Client::sendBlaster(float x, float y)
{
    sf::Packet packet;

    packet << "blaster shot" << _id << x << y;
    std::cout << packet.getData() << std::endl;
    if (_socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
        exit(84);
    }
}

void Client::sendEnnemy(int type, float x, float y)
{
    sf::Packet packet;

    packet << "ennemy spawn" << _id << type << x << y;
    std::cout << packet.getData() << std::endl;
    if (_socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
        exit(84);
    }
}

sf::Packet Client::receive()
{
    sf::Packet receivePacket;

    if (_socket.receive(receivePacket) != sf::Socket::Status::Done) {
        std::cerr << "Error : Receiving failed (maybe server down)" << std::endl;
        exit(84);
    }
    return receivePacket;
}

sf::Packet Client::WaitReceive()
{
    sf::Packet receivePacket;

    _socket.setBlocking(false);
    _socket.receive(receivePacket);
    _socket.setBlocking(true);
    return receivePacket;
}

void Client::disconnect()
{
    sf::Packet packet;

    packet << "disconnect";
    if (_socket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
        exit(84);
    }
    _socket.disconnect();
}
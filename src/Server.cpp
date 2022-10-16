/*
** EPITECH PROJECT, 2022
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"

void Server::accept()
{
    auto *client = new sf::TcpSocket;
    sf::Packet sendPacket;

    if (_listener.accept(*client) == sf::Socket::Status::Done) {
        _selector.add(*client);
        _clients.push_back(client);
    }
    sendPacket << _id;
    ++_id;
    if (client->send(sendPacket) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending ID" << std::endl;
    }
}

void Server::send(std::string const &message)
{
    sf::Packet packet;

    for (auto &client : _clients) {
        if (client->send(packet) != sf::Socket::Status::Done) {
            std::cerr << "Error : Sending failed" << std::endl;
        }
    }
}

void Server::sendPos(float x, float y)
{
    sf::Packet packet;

    packet << x << y;
    if (_clients.empty())
        return;
    for (auto &client : _clients) {
        if (client->send(packet) != sf::Socket::Status::Done) {
            std::cerr << "Error : Sending failed" << std::endl;
        }
    }
}

sf::Packet Server::receive(sf::TcpSocket *client)
{
    sf::Packet packet;
    int type = 0;
    std::vector<sf::TcpSocket *>::iterator pos;

    if (client->receive(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Receiving failed" << std::endl;
    }
    packet >> type;
    if (type == -1) {
        pos = std::find(_clients.begin(), _clients.end(), client);
        _selector.remove(*client);
        delete _clients[static_cast<unsigned long>(std::distance(_clients.begin(), pos))];
        _clients.erase(pos);
        std::cout << "Client disconnected" << std::endl;
    }
    return packet;
}
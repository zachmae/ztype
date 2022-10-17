/*
** EPITECH PROJECT, 2022
** Server.cpp
** File description:
** Server
*/

#include "Server.hpp"
#include <optional>

void Server::accept()
{
    auto *client = new sf::TcpSocket;
    sf::Packet sendPacket;

    if (_listener.accept(*client) == sf::Socket::Status::Done) {
        _selector.add(*client);
        _clients.push_back(client);
    }

    // Send id to NewClient
    sendPacket <<  _id;
    std::cout << "ID : " << _id << std::endl;
    if (client->send(sendPacket) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending ID" << std::endl;
    }

    // Send id NewClient to OldClient
    sendPacket.clear();
    sendPacket << "new_client" << _id;

    for (auto &oldClient : _clients) {
        if (oldClient != client) {
            if (oldClient->send(sendPacket) != sf::Socket::Status::Done) {
                std::cerr << "Error : Sending ID" << std::endl;
            }
        }
    }

    // Send OldClient to NewClient
    sendPacket.clear();
    sendPacket << "old_client" << _id;
    for (int i = 0; i < _id; ++i) {
        sendPacket << i;
    }
    if (client->send(sendPacket) != sf::Socket::Status::Done) {
        std::cerr << "Error : Sending ID" << std::endl;
    }

    ++_id;
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
    std::string type;
    std::vector<sf::TcpSocket *>::iterator pos;

    if (client->receive(packet) != sf::Socket::Status::Done) {
        std::cerr << "Error : Receiving failed" << std::endl;
    }
//            packet << _id << 0 << x << y;
    packet >> type;
    if (type == "disconnect") {
        /**
        * @brief DISCONNECTED CLIENT
        *
        *
        *
        */
        pos = std::find(_clients.begin(), _clients.end(), client);
        _selector.remove(*client);
        delete _clients[static_cast<unsigned long>(std::distance(_clients.begin(), pos))];
        _clients.erase(pos);
        std::cout << "Client disconnected" << std::endl;
    } else if (type == "pos_client") {
        /**
        * @brief GET POS CLIENT AND SEND TO OTHER CLIENT
        *
        *
        */
        int id;
        float x;
        float y;
        sf::Packet atEveryone;

        packet >> id >> x >> y;

        atEveryone << "client_pos" << id << x << y;
        std::cout << "server_get ID : " << id << " X : " << x << " Y : " << y << std::endl;
        for (auto a_client : _clients) {
            std::optional<sf::Socket::Status> status = std::nullopt;
            if (client != a_client && (status = a_client->send(atEveryone)) == sf::Socket::Status::Done) {
                std::cout << "server_send ID : " << id << " X : " << x << " Y : " << y << std::endl;
            } else {
                std::cerr << "Error : Sending failed " << (status ? *status : -50) << std::endl;
            }
        }
    }
      //  packet >> _x >> _y;

    return packet;
}
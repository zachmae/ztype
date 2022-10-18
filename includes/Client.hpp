/*
** EPITECH PROJECT, 2022
** client.hpp
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <SFML/Network.hpp>

/*!
 *  \addtogroup Network
 *  @{
 */

//! Class for the client of the network
class Client {
    public:
        /**
         * @brief Construct a new Client and connect to the server
         *
         * @param ip : the ip of the server you want to connect to
         * @param port : the port of the server you want to connect to
         */
        inline Client(std::string const &ip, unsigned short port) {
            sf::Packet packet;

            if (_socket.connect(ip, port, sf::seconds(15)) != sf::Socket::Status::Done) {
                std::cerr << "Error : Connection failed" << std::endl;
                exit(84);
            }
            receive() >> _id;
            std::cout << "ID : " << _id << std::endl;
        }
        inline ~Client() = default;

        [[nodiscard]] inline sf::TcpSocket &getSocket() { return _socket; }

        /**
         * @brief Send a packet to the server
         *
         * @param sf::Packet you want to send
         */
        [[deprecated]] inline void send(std::string const &message) {
            sf::Packet packet;
            packet << message << _id << 0 << message;
            if (_socket.send(packet) != sf::Socket::Status::Done) {
                std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                exit(84);
            }
        }

        /**
        * @brief Send a position to the server
        *
        * @param x position x of the player
        * @param y position y of the player
        */
        inline void sendPos(float x, float y) {
            sf::Packet packet;
            packet << "pos" << _id << x << y;
            if (_socket.send(packet) != sf::Socket::Status::Done) {
                std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                exit(84);
            }
        }

        /**
         * @brief Receive a packet from the server
         *
         * @return the sf::Packet receive
         */
        inline sf::Packet receive() { // not used
            sf::Packet receivePacket;
            if (_socket.receive(receivePacket) != sf::Socket::Status::Done) {
                std::cerr << "Error : Receiving failed (maybe server down)" << std::endl;
                exit(84);
            }
            return receivePacket;
        }

        /**
         * @brief Receive a packet from the server
         *
         * @return sf::Packet : the packet that was received
         */
        sf::Packet WaitReceive() {
            sf::Packet receivePacket;
            _socket.setBlocking(false);
            _socket.receive(receivePacket);
            _socket.setBlocking(true);
            return receivePacket;
        }

        /**
         * @brief disconnect the client from the server
         */
        inline void disconnect() {
            sf::Packet packet;
            packet << "disconnect";
            if (_socket.send(packet) != sf::Socket::Status::Done) {
                std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                exit(84);
            }
            _socket.disconnect();
        }

        /**
         * @brief Get the Id object
         *
         * @return int : the id of the client
         */
        int GetId()
        {
            return _id;
        }

    private:
        sf::TcpSocket _socket;
        int _id = 0;
};

#endif /* CLIENT_HPP_ */
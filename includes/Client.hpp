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

class Client {
    public:
        /**
         * @brief Construct a new Client and connect to the server
         *
         * @param ip
         * @param port
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

            //int type = 0;
            //receivePacket >> type;

            /*if (type == 1) {
                int id;
                float x;
                float y;

                receivePacket >> id >> x >> y;
                sf::Packet atEveryone;
                atEveryone << 1 << id << x << y;
                for (auto a_client : _clients) {
                    if (client != a_client && a_client->send(atEveryone) != sf::Socket::Status::Done) {
                        std::cerr << "Error : Sending failed" << std::endl;
                    }
                }
            }*/

            return receivePacket;
        }

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

        int GetId()
        {
            return _id;
        }

    private:
        sf::TcpSocket _socket;
        int _id = 0;
};

#endif /* CLIENT_HPP_ */
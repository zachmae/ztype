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
        Client(std::string const &ip, unsigned short port);
        inline ~Client() = default;


        /**
         * @brief Send a packet to the server
         *
         * @param sf::Packet you want to send
         */
        [[deprecated]] void send(std::string const &message);

        /**
        * @brief Send a position to the server
        *
        * @param x position x of the player
        * @param y position y of the player
        */
        void sendPos(float x, float y);

        /**
         * @brief Send the position of a blaster spawn to the server
         *
         * @param x position x of the blaster
         * @param y position y of the blaster
         */
        void sendBlaster(float x, float y);

        /**
         * @brief Send the spawn of an ennemy to the server
         *
         * @param type type of the ennemy
         * @param x position x of the blaster
         * @param y position y of the blaster
         */
        void sendEnnemy(int type, float x, float y);



        /**
         * @brief Receive a packet from the server
         *
         * @return the sf::Packet receive
         */
        inline sf::Packet receive(); // not used

        /**
         * @brief Receive a packet from the server
         *
         * @return sf::Packet : the packet that was received
         */
        sf::Packet WaitReceive();

        /**
         * @brief disconnect the client from the server
         */
        void disconnect();

        /**
         * @brief Get the Id object
         *
         * @return int : the id of the client
         */
        int GetId() { return _id; }
        [[nodiscard]] inline sf::TcpSocket &getSocket() { return _socket; }

    private:
        sf::TcpSocket _socket;
        int _id = 0;
};

#endif /* CLIENT_HPP_ */
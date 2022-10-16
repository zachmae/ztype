/*
** EPITECH PROJECT, 2022
** rtype
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** main
*/

#include <SFML/Window.hpp>
#include "Game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
    sf::Event event;
    GameStd::GameManager manager(window, event);

    return manager.run();
}
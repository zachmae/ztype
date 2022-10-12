/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Component
*/

#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

//#ifndef COMPONENT_HPP_
//#define COMPONENT_HPP_

namespace GameStd {
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;

    struct position {
        float x;
        float y;
    };

    struct velocity {
        float x;
        float y;
    };

    struct drawable {
        sf::Sprite sprite;
    };

    struct contralable {

    };

}

//#endif /* !COMPONENT_HPP_ */
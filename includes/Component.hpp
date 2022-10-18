/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Component
*/

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

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

    struct controlable {
        int id;
    };

    struct animation_basic {
        sf::IntRect rect;
        int frame_current{};
        int frame_max{};
        int frame_size{};
        float frame_time{};
    };

    struct animation_adaptative {
        sf::IntRect rect;
        int frame_current_x{};
        int frame_current_y{};
        float frame_time{};
    };

    struct resizable {
        float x;
        float y;
    };

    struct is_ship {
    };

    struct collidable {
    };

    struct is_background {
    };
}
#endif /* !COMPONENT_HPP_ */

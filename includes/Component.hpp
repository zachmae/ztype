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

/*!
 *  \addtogroup GameStd
 *  @{
 */

//! Namespace for all game related content like the components
namespace GameStd {
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;

    /**
     * @brief Component position in order to get the position of the entity in a 2D space
     *
     */
    struct position {
        float x;
        float y;
    };

    /**
     * @brief Component velocity in order to get the velocity of the entity for it to move in a 2D space
     *
     */
    struct velocity {
        float x;
        float y;
    };

    /**
     * @brief Component drawable contain the sprite of the entity in order to draw it
     *
     */
    struct drawable {
        sf::Sprite sprite;
    };

    /**
     * @brief Component controlable now contain the id of the entity to be controlled
     *
     */
    struct controlable {
        int id;
    };

    /**
     * @brief Component basic animation contain the animation of the entity in order to animate it in a generic way
     *
     */
    struct animation_basic {
        sf::IntRect rect;
        int frame_current{};
        int frame_max{};
        int frame_size{};
        float frame_time{};
    };

    /**
     * @brief Component animation adaptative contain the animation of the entity in order to animate it remotely
     *
     */
    struct animation_adaptative {
        sf::IntRect rect;
        int frame_current_x{};
        int frame_current_y{};
        float frame_time{};
    };

    /**
     * @brief Component resizable contain the scale of the entity
     *
     */
    struct resizable {
        float x;
        float y;
    };

    /**
     * @brief Component is_ship if the entity is a ship
     *
     */
    struct is_ship {
    };

    /**
     * @brief Component collider in order to handle the collisions of the entity
     *
     */
    struct collidable {
    };

    /**
     * @brief Component is_background in order to handle the parallax and all other background stuff
     *
     */
    struct is_background {
    };

    /**
     * @brief Component is_ally in order to indentify if the entity is or ally or an ennemy
     *
     */
    struct is_ally {
        bool status;
    };

    /**
     * @brief Component attack in order to handle the attack of the entity
     *
     */
    struct attack {
        int damage;
    };

    /**
     * @brief Component health in order to handle the health of the entity
     *
     */
    struct health {
        int hp;
    };

    /**
     * @brief Component is_boss in order to handle the boss of the game
     *
     */
    struct is_boss {
    };

    /**
     * @brief Component death_sfx in order to handle the death sound of the entity
     *
     */
    struct death_sfx {
        std::string key;
    };

}
#endif /* !COMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Component
*/

#include <functional>
#include <uuid/uuid.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#ifndef USERCOMPONENT_HPP_
    #define USERCOMPONENT_HPP_

//utilisateur

/**
 * @struct position
 *
 */
struct position {
    float x;
    float y;
};

/**
 * @struct velocity
 *
 * @brief velocity of the entity
 *
 */
struct velocity {
    float x;
    float y;
};

/**
 * @struct controlable
 *
 * @brief controlable of the entity
 */
struct controlable {
};

/**
 * @struct resizable
 *
 * @brief Component resizable contain the scale of the entity
 *
 */
struct resizable {
    float x;
    float y;
};

/**
 * @struct is_ship
 *
 * @brief Component is_ship if the entity is a ship
 *
 */
struct is_ship {
};

/**
 * @struct collidable
 *
 * @brief Component collider in order to handle the collisions of the entity
 *
 */
struct collidable {
};

/**
 * @struct is_background
 *
 * @brief Component is_background in order to handle the parallax and all other background stuff
 *
 */
struct is_background {
};

/**
 * @struct is_ally
 * @brief Component is_ally in order to indentify if the entity is or ally or an enemy
 *
 */
struct is_ally {
    bool status;
};

/**
 * @struct attack
 *
 * @brief Component attack in order to handle the attack of the entity
 *
 */
struct attack {
    int damage;
};

/**
 * @struct health
 *
 * @brief Component health in order to handle the health of the entity
 *
 */
struct health {
    int hp;
};

/**
 * @struct is_boss
 *
 * @brief Component is_boss in order to handle the boss of the game
 *
 */
struct is_boss {
};

struct uuid {
    char uuid[32];
};

#endif /* !USERCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Component
*/

#include <functional>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "../SceneManager/SceneManager.hpp"
#include "AudioManager.hpp"
#include "MusicManager.hpp"

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
 * @struct drawable
 *
 * @brief drawable of the entity
 */
struct drawable {
    sf::Sprite sprite;
};

/**
 * @struct controlable
 *
 * @brief controlable of the entity
 */
struct controlable {
};

/**
 * @struct clickable
 *
 * @brief Component clickable in order to handle the click of the entity (button)
 */
struct clickable {
    std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)> callback;
};

/**
 * @struct animation_basic
 *
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
 * @struct animation_adaptative
 *
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

/**
 * @struct death_sfx
 *
 * @brief Component death_sfx in order to handle the death sound of the entity
 *
 */
struct death_sfx {
    std::string key;
};

/**
 * @struct clickable sfx
 *
 * @brief Component clickable_sfx in order to handle the sound of the click of the entity (button)
 */
struct clickable_sfx {
    std::string key;
};

/**
 * @brief Component value_score so that the player earn points when the entity is killed
 *
 */
struct value_score {
    int value;
};

/**
 * @brief Component text in order to handle the text of the entity
 *
 */
struct text {
    std::string text_str;
};

/**
 * @brief Component is_score in order to handle the score of the player
 *
 */
struct is_score {
};

/**
 * @brief uuid not used yet
 *
 */
struct uuid {
    char uuid[32];
};

/**
 * @brief Component is_text_button_dict in order to handle the button text
 *
 */
struct is_text_button_dict {
    std::string key;
};

/**
 * @brief Component is_music in order to handle the music volume text
 *
 */
struct is_music {
};

/**
 * @brief Component is_audio in order to handle the audio volume text
 *
 */
struct is_audio {
};

#endif /* !USERCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** game_init
*/

#include "Init.hpp"

namespace User {
    namespace Game {

    void background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name, float parallax_speed)
    {
        entity_t background = scene.Get("game").SpawnEntity();
        reg.add_component<drawable>(background, {sprite_manager.Get(name)});
        reg.add_component<position>(background, {0, 0});
        reg.add_component<velocity>(background, {parallax_speed, 0});
        reg.add_component<is_background>(background, {});
    }

    void ship_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, bool mine)
    {
        entity_t ship = scene.Get("game").SpawnEntity();
        reg.add_component<drawable>(ship, {sprite_manager.Get(name)});
        reg.add_component<position>(ship, {100, 300});
        reg.add_component<velocity>(ship, {2, 2});
        reg.add_component<resizable>(ship, {2, 2});
        reg.add_component<animation_adaptative>(ship, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
        if (mine)
            reg.add_component<controlable>(ship, {});
        reg.add_component<is_ship>(ship, {});
        reg.add_component<is_ally>(ship, {true});
        reg.add_component<collidable>(ship, {});
        reg.add_component<health>(ship, {1});
        reg.add_component<attack>(ship, {0});
        reg.add_component<death_sfx>(ship, {"explosion"});
    }

    }
}

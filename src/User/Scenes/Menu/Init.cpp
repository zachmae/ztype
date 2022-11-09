/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** game_init
*/

#include <functional>

#include "Init.hpp"

namespace User {
    namespace Menu {

        void background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name, float parallax_speed)
        {
            entity_t background = scene.Get("menu").SpawnEntity();
            reg.add_component<drawable>(background, {sprite_manager.Get(name)});
            reg.add_component<position>(background, {0, 0});
            reg.add_component<velocity>(background, {parallax_speed, 0});
            reg.add_component<is_background>(background, {});
        }

        void button_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, std::pair<float, float> pos, std::function<void(SceneManager_ref<std::string>)> callback)
        {
            entity_t button = scene.Get("menu").SpawnEntity();
            reg.add_component<drawable>(button, {sprite_manager.Get(name)});
            reg.add_component<position>(button, {pos.first, pos.second});
            reg.add_component<animation_adaptative>(button, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
            reg.add_component<clickable>(button, {callback});
            reg.add_component<clickable_sfx>(button, {"explosion"});
        }

    }
}

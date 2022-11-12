/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** game_init
*/

#include <functional>

#include "Init.hpp"
#include "Languages.hpp"

        void User::Menu::background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name)
        {
            entity_t background = scene.Get("menu").SpawnEntity();
            reg.add_component<drawable>(background, {sprite_manager.Get(name)});
            reg.add_component<position>(background, {0, 0});
            reg.add_component<is_background>(background, {});
        }

        void User::Menu::button_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, std::pair<float, float> pos, clickable callback, std::string str)
        {
            entity_t button = scene.Get("menu").SpawnEntity();
            reg.add_component<drawable>(button, {sprite_manager.Get(name)});
            reg.add_component<position>(button, {pos.first, pos.second});
            reg.add_component<clickable>(button, std::move(callback));
            reg.add_component<clickable_sfx>(button, {"explosion"});
            reg.add_component<text>(button, {std::string("")});
            reg.add_component<is_text_button_dict>(button, {str});
        }
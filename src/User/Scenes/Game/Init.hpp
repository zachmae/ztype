/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Game
*/

#include <string>

#include "../../UserComponent.hpp"
#include "../../../ProjectManager/Ecs.hpp"

#include "../../../SceneManager/SceneManager.hpp"
#include "../../../SpriteManager.hpp"
#include "../../../AudioManager.hpp"

namespace User {
    namespace Game {

    void background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name, float parallax_speed);

    void ship_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, bool mine);

    }
}
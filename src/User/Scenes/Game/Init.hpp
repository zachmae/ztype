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

        /**
         * @brief create a background object from the given attributes
         *
         * @param reg : the reference to the registry
         * @param sprite_manager : the reference to the sprite manager
         * @param scene : the reference to the scene manager
         * @param name : the name of the background in the sprite manager
         * @param parallax_speed : the speed of the background for the parallax (0 for a static one)
         */
        void background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name, float parallax_speed);

        /**
         * @brief create a player object from the given attributes
         *
         * @param reg : the reference to the registry
         * @param sprite_manager : the reference to the sprite manager
         * @param scene : the reference to the scene manager
         * @param audioManager : the reference to the audio manager
         * @param name : the name of the player in the sprite manager
         * @param mine : if the player is the local player (false by default)
         */
        void ship_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, bool mine);

    }
}
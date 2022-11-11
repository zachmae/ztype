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
    namespace Menu {

        /**
         * @brief create a background object from the given attributes
         *
         * @param reg : the reference to the registry
         * @param sprite_manager : the reference to the sprite manager
         * @param scene : the reference to the scene manager
         * @param name : the name of the background in the sprite manager
         * @param parallax_speed : the speed of the background for the parallax (0 for a static one)
         */
        void background_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, std::string name);

        /**
         * @brief create a button object from the given attributes not complete at the moment (where is the callback ?)
         *
         * @param reg : the reference to the registry
         * @param sprite_manager : the reference to the sprite manager
         * @param scene : the reference to the scene manager
         * @param audioManager : the reference to the audio manager
         * @param name : the name of the button in the sprite manager
         */
        void button_generation(Registry_ref reg, SpriteManager_ref<std::string> sprite_manager, SceneManager_ref<std::string> scene, AudioManager_ref<std::string> audioManager, std::string name, std::pair<float, float> pos, clickable callback);

    }
}
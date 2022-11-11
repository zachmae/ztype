//ProjectManager
#include "ProjectManager/Ecs.hpp"

//SceneManager
#include "SceneManager/SceneManager.hpp"
#include "SceneManager/Scene.hpp"
#include "SceneManager/SceneComponent.hpp"

#include "../ClientComponent.hpp"

#include "SpriteManager.hpp"
#include "AudioManager.hpp"

#include "System.hpp"

#ifndef USERSYSTEM_HPP_
    #define USERSYSTEM_HPP_

namespace User {

    /**
     * @brief control the user input
     *
     * @param r : the reference to the registry
     * @param e : the reference to the event manager
     * @param _spriteManager : the reference to the sprite manager
     * @param _audioManager : the reference to the audio manager
     */
    void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager, AudioManager<std::string>& _audioManager, SceneManager_ref<std::string> scene)
    {
        auto &controllables = r.get_components<controlable>();
        auto &velocities = r.get_components<velocity>();
        auto &positions = r.get_components<position>();
        auto &are_ships = r.get_components<is_ship>();

        for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
            if (velocities[i] && controllables[i] && e.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    velocities[i]->y = -10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    velocities[i]->y = 10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    velocities[i]->x = -10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    velocities[i]->x = 10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    User::bullet_creation_system(r, positions[i]->x, positions[i]->y, _spriteManager, _audioManager, scene);
                }
                if (i < are_ships.size() && are_ships[i])
                    User::animate_ship_system(r, i, e.key.code);
            }
        }
    }
    template<typename Key>
    void User::click_system(Registry_ref reg, SceneManager_ref<Key> scene, Event_ref event, Window_ref window)
    {
        auto &clickables = reg.get_components<clickable>();
        auto &drawables = reg.get_components<drawable>();
        auto &positions = reg.get_components<position>();

        if (event.type == sf::Event::MouseButtonPressed) {
            for (size_t i = 0; i < drawables.size() && i < positions.size() && i < clickables.size(); ++i) {
                if (drawables[i] && positions[i] && clickables[i]) {
                    if (drawables[i]->sprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) {
                        clickables[i]->callback(scene);
                    }
                }
            }
        }
        if (event.type == sf::Event::KeyReleased  && event.key.code == sf::Keyboard::Escape) {
            pop_settings(scene);
        }
    }

    template<typename Key>
    using SceneManager_ref = SceneManager<Key> &;

    /**
     * @brief display the scene related to the sprite
     *
     * @param _ecs : the reference to the ecs
     * @param sm : the reference to the scene manager
     * @param window : the reference to the window
     */
    inline void displayscene_system(Registry_ref _ecs, SceneManager_ref<std::string> sm, Window_ref window)
    {
        std::vector<int> vi = sm.GetDisplayOrderOfSceneID();

        auto &drawables = _ecs.get_components<drawable>();
        auto &positions = _ecs.get_components<position>();
        auto &SceneIds = _ecs.get_components<SceneId>();


        for (const auto& sceneId: vi) {
            for (size_t i = 0; i < drawables.size() && i < positions.size() && i < SceneIds.size(); ++i) {
                if (drawables[i] && positions[i] && SceneIds[i] && SceneIds[i]->_sceneId == sceneId) {
                    drawables[i]->sprite.setPosition({positions[i]->x, positions[i]->y});
                    window.draw(drawables[i]->sprite);
               }
            }
        }
    }
}

#endif /* !USERSYSTEM_HPP_ */
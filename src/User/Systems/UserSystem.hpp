//ProjectManager
#include "ProjectManager/Ecs.hpp"

//SceneManager
#include "SceneManager/SceneManager.hpp"
#include "SceneManager/Scene.hpp"
#include "SceneManager/SceneComponent.hpp"

#include "../UserComponent.hpp"

#include "SpriteManager.hpp"
#include "AudioManager.hpp"

#include "User/Systems/System.hpp"

#ifndef USERSYSTEM_HPP_
    #define USERSYSTEM_HPP_

namespace User {

    inline void position_system(registry &r)
    {
        auto &positions = r.get_components<struct position>();
        auto &velocities = r.get_components<struct velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            if (positions[i] && velocities[i]) {
                positions[i]->x += velocities[i]->x;
                positions[i]->y += velocities[i]->y;
            }
        }
        for (size_t i = 0; i < velocities.size(); ++i) {
            if (velocities[i]) {
                velocities[i]->y = 0;
                velocities[i]->x = 0;
            }
        }
    }

    void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager, AudioManager<std::string>& _audioManager)
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
                    User::bullet_creation_system(r, positions[i]->x, positions[i]->y, _spriteManager, _audioManager);
                }
                if (i < are_ships.size() && are_ships[i])
                    User::animate_ship_system(r, i, e.key.code);
            }
        }
    }

    template<typename Key>
    using SceneManager_ref = SceneManager<Key> &;

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

    inline void draw_system(registry &r, Window_ref w)
    {
        auto &drawables = r.get_components<drawable>();
        auto &positions = r.get_components<position>();

        for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i) {
            if (drawables[i] && positions[i]) {
                drawables[i]->sprite.setPosition({positions[i]->x, positions[i]->y});
                w.draw(drawables[i]->sprite);
            }
        }
    }
}

#endif /* !USERSYSTEM_HPP_ */
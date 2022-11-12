//ProjectManager
#include "ProjectManager/Ecs.hpp"

//SceneManager
#include "SceneManager/SceneManager.hpp"
#include "SceneManager/Scene.hpp"
#include "SceneManager/SceneComponent.hpp"

#include "../ClientComponent.hpp"

#include "SpriteManager.hpp"
#include "AudioManager.hpp"

#include <codecvt>
#include <locale>

#include "System.hpp"
#include "Globals.hpp"

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
     * @param client : the reference to the client
     */
    void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager, AudioManager<std::string>& _audioManager, SceneManager_ref<std::string> scene, Client &client)
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
                    User::bullet_creation_system(r, positions[i]->x, positions[i]->y, _spriteManager, _audioManager, scene, client);
                }
                if (i < are_ships.size() && are_ships[i])
                    User::animate_ship_system(r, i, e.key.code);
            }
        }
    }
    template<typename Key>
    void User::click_system(Registry_ref reg, SceneManager_ref<Key> scene, Event_ref event, Window_ref window, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
    {
        auto &clickables = reg.get_components<clickable>();
        auto &drawables = reg.get_components<drawable>();
        auto &positions = reg.get_components<position>();

        if (event.type == sf::Event::MouseButtonPressed) {
            for (size_t i = 0; i < drawables.size() && i < positions.size() && i < clickables.size(); ++i) {
                if (drawables[i] && positions[i] && clickables[i]) {
                    if (drawables[i]->sprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) {
                        clickables[i]->callback(scene, am, mm);
                    }
                }
            }
        }
        if (event.type == sf::Event::KeyReleased  && event.key.code == sf::Keyboard::Escape) {
            pop_settings(scene, am, mm);
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
        auto &animation_adaptatives = _ecs.get_components<struct animation_adaptative>();
        auto &resizables = _ecs.get_components<struct resizable>();
        auto &are_allies = _ecs.get_components<is_ally>();
        auto &textables = _ecs.get_components<text>();
        bool collision_box = Globals::debug_mode;

        animation_basic_system(_ecs);
        for (const auto& sceneId: vi) {
            for (size_t i = 0; i < drawables.size() && i < positions.size() && i < SceneIds.size(); ++i) {
                if (drawables[i] && positions[i] && SceneIds[i] && SceneIds[i]->_sceneId == sceneId) {
                    if (i < positions.size() && positions[i])
                        drawables[i]->sprite.setPosition(positions[i]->x, positions[i]->y);
                    if (i < animation_adaptatives.size() && animation_adaptatives[i])
                        drawables[i]->sprite.setTextureRect(animation_adaptatives[i]->rect);
                    if (i < resizables.size() && resizables[i])
                        drawables[i]->sprite.setScale(resizables[i]->x, resizables[i]->y);
                    if (collision_box && i < are_allies.size()) {
                        // display_debug_mode(window, drawables[i]->sprite, are_allies[i]);
                    }
                    // drawables[i]->sprite.setPosition({positions[i]->x, positions[i]->y});
                    window.draw(drawables[i]->sprite);
               }
            }
            for (size_t i = 0; i < textables.size(); ++i) {
                if (textables[i] && positions[i] && SceneIds[i] && SceneIds[i]->_sceneId == sceneId) {
                    sf::Text text_object;
                    text_object.setFont(Globals::font);
                    static std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
                    text_object.setString(utf8_conv.from_bytes(textables[i]->text_str));
                    if (i < positions.size() && positions[i])
                        text_object.setPosition(positions[i]->x, positions[i]->y);
                    if (i < resizables.size() && resizables[i])
                        text_object.setScale(resizables[i]->x, resizables[i]->y);
                    window.draw(text_object);
                }
            }
        }
    }
}

#endif /* !USERSYSTEM_HPP_ */
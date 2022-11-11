/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager/SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

#include "ProjectManager/ProjectComponent.hpp"
#include "SceneManager/SceneComponent.hpp"
#include "SceneManager/SceneManager.hpp"

#include "Systems/System.hpp"
#include "Systems/ClientSystem.hpp"

#include "Scenes/Game/Init.hpp" // WHAT THE FUCK

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

#include "ClientComponent.hpp"
#include "ClientManager.hpp"

#include "Globals.hpp"

/**
 * @brief namespace User
 *
 * @author perry.chouteau@epitech.eu
 */
namespace User {

    /**
     * @brief init the scenes
     *
     * @param r : the reference to the registry
     * @param sm : the reference to the sprite manager
     * @param am : the reference to the audio manager
     * @param mm : the reference to the music manager
     * @param scene : the reference to the scene manager
     */
    void ClientManager::InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm, SceneManager_ref<std::string> scene)
    {
        scene.Get("tutorial").SetZIndex(-1);
        scene.Get("game").SetZIndex(-1);
        scene.Get("menu").SetZIndex(-1);
        scene.Get("loading").SetZIndex(-1);
        scene.Get("settings").SetZIndex(-1);
        scene.Get("lose").SetZIndex(-1);
        scene.Get("win").SetZIndex(-1);

        User::Game::background_generation(r, sm, scene, "background_back", -0.1f);
        User::Game::background_generation(r, sm, scene, "background_stars", -0.2f);
        User::Game::background_generation(r, sm, scene, "background_planets_back", -0.5f);
        User::Game::background_generation(r, sm, scene, "background_planets_front", -0.8f);
        User::Game::ship_generation(r, sm, scene, am, "ship", true);

        entity_t score = scene.Get("game").SpawnEntity();
        r.add_component<text>(score, {std::string("")});
        r.add_component<is_score>(score, {});
        r.add_component<position>(score, {0, 0});
        r.add_component<resizable>(score, {2, 2});
        mm.play("epitomize");
    }

    /**
     * @brief
     *
     * @tparam Key
     * @param reg
     * @param scenes
     * @param window
     * @param event
     */
    template <typename Key>
    void ClientManager::UpdateScene(Registry_ref reg, SceneManager<Key> &scene, sf::RenderWindow &window, sf::Event &event)
    {
        ;
    }

    /**
     * @brief Close the Client
     *
     */
    void ClientManager::Close()
    {
        _client.disconnect();
    }

    /**
     * @brief Update Event System
     *
     * @tparam Key
     * @param reg : the reference to the registry
     * @param event : the reference to the event
     * @param window : the reference to the window
     * @param sm : the reference to the sprite manager
     * @param am : the reference to the audio manager
     */
    template<typename Key>
    void ClientManager::UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am)
    {
        User::control_system(reg, event, sm, am, _client);
    }

    /**
     * @brief Update Client
     *
     * @tparam Key
     * @param reg : the reference to the registry
     * @param window : the reference to the window
     * @param sm : the reference to the sprite manager
     * @param am : the reference to the audio manager
     */
    template<typename Key>
    void ClientManager::UpdateClient(Registry_ref reg, SceneManager_ref<std::string> scenes, SpriteManager_ref<Key> _sm, AudioManager_ref<Key> am)
    {
        sf::Packet sfp = _client.WaitReceive();
        if (sfp.getData() != NULL) { //cond doesn't work
            std::string comparator;
            sfp >> comparator;
            if (comparator == "new_client") {
                //createNewClient(Registry_ref reg, SceneManager_ref<Key> scenes, SpriteManager_ref<Key> _sm, Client &client);
                /**
                * @brief OLD CLIENT GET NEW SHIP
                */
                int newCliId = 0;
                sfp >> newCliId;
                // comment on stock les id des autres
                entity_t newCliEntity = scenes.Get("game").SpawnEntity();
                reg.add_component<drawable>(newCliEntity, {_sm.Get("ship")});
                reg.add_component<position>(newCliEntity, {100, 300});
                reg.add_component<velocity>(newCliEntity, {2, 2});
                reg.add_component<resizable>(newCliEntity, {2, 2});
                reg.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                reg.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                reg.add_component<is_ship>(newCliEntity, {});
                reg.add_component<is_ally>(newCliEntity, {true});
                reg.add_component<collidable>(newCliEntity, {});
                reg.add_component<health>(newCliEntity, {1});
                reg.add_component<attack>(newCliEntity, {0});
                reg.add_component<death_sfx>(newCliEntity, {"explosion"});
            } else if (comparator == "old_client") {
                //createOldClient(Registry_ref reg, SceneManager_ref<Key> scenes, SpriteManager_ref<Key> _sm, Client &client);

                /**
                * @brief NEW CLIENT GET OLD SHIP
                */
                int amount = 0;
                int newCliId = 0;
                sfp >> amount;
                for (sfp >> newCliId; amount != 0; sfp >> newCliId, amount--) {
                    if (_client.GetId() != newCliId) {
                        entity_t newCliEntity = reg.spawn_entity();
                        reg.add_component<drawable>(newCliEntity, {_sm.Get("ship")});
                        reg.add_component<position>(newCliEntity, {100, 200});
                        reg.add_component<velocity>(newCliEntity, {2, 2});
                        reg.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                        reg.add_component<resizable>(newCliEntity, {2, 2});
                        reg.add_component<is_ship>(newCliEntity, {});
                        reg.add_component<collidable>(newCliEntity, {});
                        reg.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                    }
                }
            } else if (comparator == "client_pos") {
               //editClientPos(Registry_ref reg, SceneManager_ref<Key> scenes, SpriteManager_ref<Key> _sm, Client &client);
                /**
                 * @brief GET SHIP POSITION
                 */
                int id = 0;
                float x = 0;
                float y = 0;
                sfp >> id >> x >> y;
                auto &positions = reg.get_components<position>();
                auto &ids = reg.get_components<int>();
                int i = 0;
                for(auto &_id : ids) {
                    if (_id != std::nullopt && _id == id) {
                        if (positions[i] != std::nullopt)
                            reg.add_component<position>(reg.entity_from_index(i), {x, y});
                    }
                    ++i;
                }
            } else if (comparator == "blaster_pos") {
                int id = 0;
                float x = 0;
                float y = 0;
                sfp >> id >> x >> y;
                entity_t bullet = reg.spawn_entity();
                reg.add_component<drawable>(bullet, {_sm.Get("bullet")});
                reg.add_component<position>(bullet, {x, y});
                reg.add_component<velocity>(bullet, {10, 0});
                reg.add_component<animation_basic>(bullet, {sf::IntRect(0, 34, 50, 17), 0, 8, 50, 0.1f});
                reg.add_component<collidable>(bullet, {});
                reg.add_component<is_ally>(bullet, {true});
                reg.add_component<attack>(bullet, {10});
                reg.add_component<health>(bullet, {1});
                am.play("blaster");
            } else {
                std::cout << "unknow type" << std::endl;
            }
        }
        /**
         * @brief SEND SHIP POSITION
         */
        sf::Packet packet;
        auto &positions = reg.get_components<position>();

        if (positions[4] != std::nullopt) {
            packet << "pos_client" << _client.GetId() << positions[4].value().x << positions[4].value().y;
            if (_client.getSocket().send(packet) != sf::Socket::Status::Done) {
                std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                exit(84);
            }
        }
    }

    /**
     * @brief Update Window System
     *
     * @tparam Key
     * @param reg : the reference to the registry
     * @param scenes : the reference to the scene manager
     * @param window : the reference to the window
     * @param _sm : the reference to the sprite manager
     */
    template<typename Key>
    void ClientManager::UpdateWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, SpriteManager_ref<Key> sm)
    {
        //all system
        User::update_score(reg);
        User::enemy_system(reg, sm, window);
        User::boss_magic_system(reg, sm, window);
        User::position_system(reg, window, _client);
        User::draw_system(reg, window);
        User::displayscene_system(reg, scene, window);

    //    draw_system(reg, window);

    }

    /**
     * @brief Update Post Window System
     *
     * @tparam Key
     * @param reg : the reference to the registry
     * @param scene : the reference to the scene manager
     * @param window : the reference to the window
     * @param am : the reference to the audio manager
     */
    template<typename Key>
    bool ClientManager::UpdatePostWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, AudioManager_ref<std::string> am)
    {
        User::collision_system(reg, am);
        User::remove_out_of_screen_system(reg, window);
        return User::check_lose_system(reg, scene);
    }

}
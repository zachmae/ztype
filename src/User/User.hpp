/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager/SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

#include "ProjectManager/ProjectComponent.hpp"
#include "UserComponent.hpp"
#include "SceneManager/SceneComponent.hpp"
#include "SceneManager/SceneManager.hpp"

#include "Systems/System.hpp"
#include "Systems/UserSystem.hpp"

#include "Scenes/Game/Game.hpp" // WHAT THE FUCK

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

#include "UserManager.hpp"

///**
// * @brief namespace User
// *
// */

namespace User {

    /**
     * @brief
     *
     * @param r
     * @param sm
     * @param scene
     */
    [[deprecated]]
    void UserManager::InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, AudioManager_ref<std::string> am, SceneManager_ref<std::string> scene)
    {
        scene.Get("tutorial").SetZIndex(-1);
        scene.Get("game").SetZIndex(-1);
        scene.Get("menu").SetZIndex(-1);
        scene.Get("loading").SetZIndex(-1);
        scene.Get("settings").SetZIndex(-1);
        scene.Get("lose").SetZIndex(-1);
        scene.Get("win").SetZIndex(-1);

        std::cout << "InitScene" << std::endl;
        User::background_generation(r, sm, scene, "background_back", -0.1f);
        std::cout << "bg 1 done" << std::endl;
        User::background_generation(r, sm, scene, "background_stars", -0.2f);
        User::background_generation(r, sm, scene, "background_planets_back", -0.5f);
        User::background_generation(r, sm, scene, "background_planets_front", -0.8f);
        std::cout << "InitScene mid" << std::endl;
        User::ship_generation(r, sm, scene, am, "ship", true);
    }

    template <typename Key>
    void UserManager::UpdateScene(Registry_ref reg, SceneManager<Key> &scene)
    {
    }

    void UserManager::Close()
    {
        _client.disconnect();
    }

    template<typename Key>
    void UserManager::UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am)
    {
        User::control_system(reg, event, sm, am);
    }

    template<typename Key>
    void UserManager::UpdateClient(Registry_ref reg, SceneManager_ref<std::string> scenes, SpriteManager_ref<Key> _sm, AudioManager_ref<Key> am)
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
                entity_t newCliEntity = scenes.Get("Game").SpawnEntity();
                reg.add_component<drawable>(newCliEntity, {_sm.Get("ship")});
                reg.add_component<position>(newCliEntity, {100, 400});
                reg.add_component<velocity>(newCliEntity, {2, 2});
                reg.add_component<controlable>(newCliEntity, {});
                reg.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                reg.add_component<resizable>(newCliEntity, {2, 2});
                reg.add_component<is_ship>(newCliEntity, {});
                reg.add_component<collidable>(newCliEntity, {});
                reg.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                reg.add_component<is_ally>(newCliEntity, {true});
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

    template<typename Key>
    void UserManager::UpdateWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, SpriteManager_ref<Key> sm)
    {
        //all system
        User::ennemy_system(reg, sm, window);
        User::boss_magic_system(reg, sm, window);
        User::position_system(reg, window/*, _client*/);
        User::draw_system(reg, window);
        User::displayscene_system(reg, scene, window);
        User::position_system(reg);

    //    draw_system(reg, window);

    }

    template<typename Key>
    void UserManager::UpdatePostWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, AudioManager_ref<std::string> am)
    {
        User::collision_system(reg, am);
        User::remove_out_of_screen_system(reg, window);
    }

}
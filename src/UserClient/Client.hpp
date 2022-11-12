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

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

#include "ClientComponent.hpp"
#include "ClientManager.hpp"

#include "Globals.hpp"

//Scenes
#include "Scenes/Game/Init.hpp"

#include "Scenes/Menu/Init.hpp"
#include "Scenes/Menu/ClickActions.hpp"

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
        scene.Get("game").SetZIndex(1);
        scene.Get("menu").SetZIndex(-5);
        scene.Get("loading").SetZIndex(-1);
        scene.Get("settings").SetZIndex(-1);
        scene.Get("lose").SetZIndex(-1);
        scene.Get("win").SetZIndex(-1);

        int i = 0;
        User::Game::background_generation(r, sm, scene, "background_back", -0.1f);
        User::Game::background_generation(r, sm, scene, "background_stars", -0.2f);
        User::Game::background_generation(r, sm, scene, "background_planets_back", -0.5f);
        User::Game::background_generation(r, sm, scene, "background_planets_front", -0.8f);
        User::Game::ship_generation(r, sm, scene, am, "ship", true);

        User::Menu::background_generation(r, sm, scene, "white_shadow");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(400, 200), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(back_to_game)}, "start_button");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(400, 800), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(exit_game)}, "exit_button");
        User::Menu::button_generation(r, sm, scene, am, "left_button", std::pair<float, float>(300, 400), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(downgrade_music)}, "");
        User::Menu::button_generation(r, sm, scene, am, "right_button", std::pair<float, float>(700, 400), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(upgrade_music)}, "");
        User::Menu::button_generation(r, sm, scene, am, "left_button", std::pair<float, float>(300, 600), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(downgrade_audio)}, "");
        User::Menu::button_generation(r, sm, scene, am, "right_button", std::pair<float, float>(700, 600), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(upgrade_audio)}, "");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(1300, 200), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(switch_language_to_fr)}, "french_button");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(1300, 400), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(switch_language_to_eng)}, "english_button");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(1300, 600), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(switch_language_to_jap)}, "japanese_font");
        User::Menu::button_generation(r, sm, scene, am, "button", std::pair<float, float>(1300, 800), {static_cast<std::function<void(SceneManager_ref<std::string>, AudioManager_ref<std::string>, MusicManager_ref<std::string>)>>(switch_language_to_spa)}, "spanish_font");


        entity_t score = scene.Get("game").SpawnEntity();
        r.add_component<text>(score, {std::string("")});
        r.add_component<is_score>(score, {});
        r.add_component<position>(score, {0, 0});
        r.add_component<resizable>(score, {2, 2});

        entity_t header_music_text = scene.Get("menu").SpawnEntity();
        r.add_component<text>(header_music_text, {std::string("")});
        r.add_component<is_text_button_dict>(header_music_text, {std::string("header_music_text")});
        r.add_component<position>(header_music_text, {430, 350});
        r.add_component<resizable>(header_music_text, {1, 1});

        entity_t music_text = scene.Get("menu").SpawnEntity();
        r.add_component<text>(music_text, {std::string("")});
        r.add_component<is_music>(music_text, {});
        r.add_component<position>(music_text, {520, 400});
        r.add_component<resizable>(music_text, {2, 2});

        entity_t header_audio_text = scene.Get("menu").SpawnEntity();
        r.add_component<text>(header_audio_text, {std::string("")});
        r.add_component<is_text_button_dict>(header_audio_text, {std::string("header_audio_text")});
        r.add_component<position>(header_audio_text, {430, 550});
        r.add_component<resizable>(header_audio_text, {1, 1});

        entity_t audio_text = scene.Get("menu").SpawnEntity();
        r.add_component<text>(audio_text, {std::string("")});
        r.add_component<is_audio>(audio_text, {});
        r.add_component<position>(audio_text, {520, 600});
        r.add_component<resizable>(audio_text, {2, 2});

        User::update_button_language(r);
        User::update_music_volume_text(r, mm);
        User::update_audio_volume_text(r, am);
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
    void ClientManager::UpdateScene(Registry_ref reg, SceneManager<Key> &scene, sf::RenderWindow &window, sf::Event &event, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
    {
        User::click_system(reg, scene, event, window, am, mm);
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
    void ClientManager::UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am, SceneManager_ref<Key> scene)
    {
        User::control_system(reg, event, sm, am, scene, _client);
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
                        entity_t newCliEntity = scenes.Get("game").SpawnEntity();
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
                entity_t bullet = scenes.Get("game").SpawnEntity();
                reg.add_component<drawable>(bullet, {_sm.Get("bullet")});
                reg.add_component<position>(bullet, {x, y});
                reg.add_component<velocity>(bullet, {10, 0});
                reg.add_component<animation_basic>(bullet, {sf::IntRect(0, 34, 50, 17), 0, 8, 50, 0.1f});
                reg.add_component<collidable>(bullet, {});
                reg.add_component<is_ally>(bullet, {true});
                reg.add_component<attack>(bullet, {10});
                reg.add_component<health>(bullet, {1});
                am.play("blaster");
            } else if (comparator == "ennemy_gen") {
                int id = 0;
                int type = 0;
                float x = 0;
                float y = 0;
                sfp >> id >> type >> x >> y;
                entity_t enemy = scenes.Get("game").SpawnEntity();
                if (type == 0) {
                    reg.add_component<drawable>(enemy, {_sm.Get("enemy")});
                    reg.add_component<position>(enemy, {x, y});
                    reg.add_component<velocity>(enemy, {-3, 0});
                    reg.add_component<animation_adaptative>(enemy, {sf::IntRect(0, 0, 64, 64), 0, 0, 0.5f});
                    reg.add_component<collidable>(enemy, {});
                    reg.add_component<is_ally>(enemy, {false});
                    reg.add_component<health>(enemy, {20});
                    reg.add_component<attack>(enemy, {10});
                    reg.add_component<value_score>(enemy, {10});
                } else if (type == 1) {
                    reg.add_component<drawable>(enemy, {_sm.Get("enemy_02")});
                    reg.add_component<position>(enemy, {x, y});
                    reg.add_component<velocity>(enemy, {-5, 0});
                    reg.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 32, 32), 0, 2, 32, 0.2f});
                    reg.add_component<collidable>(enemy, {});
                    reg.add_component<is_ally>(enemy, {false});
                    reg.add_component<health>(enemy, {1});
                    reg.add_component<attack>(enemy, {10});
                    reg.add_component<value_score>(enemy, {1});
                } else if (type == 2) {
                    reg.add_component<drawable>(enemy, {_sm.Get("enemy_03")});
                    reg.add_component<position>(enemy, {x, y});
                    reg.add_component<velocity>(enemy, {-1, 0});
                    reg.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 96, 96), 0, 4, 96, 0.3f});
                    reg.add_component<collidable>(enemy, {});
                    reg.add_component<is_ally>(enemy, {false});
                    reg.add_component<health>(enemy, {40});
                    reg.add_component<attack>(enemy, {10});
                    reg.add_component<value_score>(enemy, {100});
                } else if (type == 3) {
                    reg.add_component<drawable>(enemy, {_sm.Get("boss")});
                    reg.add_component<position>(enemy, {x, y});
                    reg.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 100, 100), 0, 13, 100, 0.2f});
                    reg.add_component<collidable>(enemy, {});
                    reg.add_component<resizable>(enemy, {4, 4});
                    reg.add_component<is_ally>(enemy, {false});
                    reg.add_component<health>(enemy, {100});
                    reg.add_component<attack>(enemy, {100});
                    reg.add_component<value_score>(enemy, {1000});
                    reg.add_component<is_boss>(enemy, {});
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
        User::update_button_language(reg);
        User::enemy_system(reg, sm, window, scene, _client);
        User::boss_magic_system(reg, sm, window, scene);
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
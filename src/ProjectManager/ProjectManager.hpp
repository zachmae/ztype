/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectManager
*/

#ifndef PROJECTMANAGER_HPP_
#define PROJECTMANAGER_HPP_

#include <fstream>
//Std
#include <tuple>
#include <type_traits> //std::is_same_v
#include <iostream>

//sfml
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

//json
#include "../nlohmann/json.hpp"

//User
#include "../User.hpp"

//UsefullLib
#include "../SpriteManager.hpp"
#include "../MusicManager.hpp"
#include "../AudioManager.hpp"
#include "../SceneManager/SceneManager.hpp"

#include "ProjectComponentManager.hpp"
#include "../SceneManager/SceneComponentManager.hpp"
#include "../UserComponentManager.hpp"


namespace GameStd {

    using json = nlohmann::json;
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;
    using Music_ref = sf::Music &;
    using Sound_ref = sf::Sound &;
    using SpriteManager_ref = SpriteManager<std::string> &;
    using json = nlohmann::json;

    //
    class ProjectManager {
        public:

            ProjectManager(std::string jsonfile)
            : _window(CreateWindow(jsonfile)), _sm(), _am(), _mm()
            {
                config_extractor<project_config::components_list>::function(_ecs); //sys
                config_extractor<scene_config::components_list>::function(_ecs); //sys
                config_extractor<user_config::components_list>::function(_ecs); //user
                json file = json::parse(std::ifstream(jsonfile.c_str()));

                InitWindow(file);
                InitSprites(file);
                InitSounds(file);
                InitScenes(file);
            };

            ~ProjectManager() = default;

            Window_ref GetWindow()
            {
                return _window;
            };

            Event_ref GetEvent()
            {
                return _event;
            };

            SpriteManager_ref GetSpriteManager()
            {
                return _sm;
            };

/*            [[deprecated]]
            int Start()
            {
                User::InitScene(_ecs, _sm, _scenes,);
                while (_window.isOpen()) {
                    _window.clear();
                    User::UpdateScene(_ecs, _scenes);

                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _window.close();
                            return 0;
                        }
                        User::CloseEvent(_event, _window);
                        User::UpdateEventSystem(_ecs, _event, _window);
                    }
                    User::UpdateWindowSystem(_ecs, _scenes, _window);
                    _window.display();
                }
                return 0;
            }
*/
////////////////////////////////////////////////////////////////////////////////////////////////

            /**
             * @brief Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int Start(std::string const &ip, unsigned short port)
            {
//                _ecs.add_component<>
                Client client(ip, port);
                _mm.play("epitomize");
                std::cout << "hey" << std::endl;
                User::InitScene(_ecs, _sm, _am, _scenes, client);
                std::cout << "bonjour" << std::endl;
                while (_window.isOpen()) { // run the program as long as the window is open
                    _window.clear();
                    User::UpdateScene(_ecs, _scenes);
                    // check all the window's events that were triggered since the last iteration of the loop
                    std::cout << "yooo" << std::endl;
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            client.disconnect();
                            _window.close();
                            return 0;
                        }
                        User::CloseEvent(_event, _window);
                        User::UpdateEventSystem(_ecs, _event, _window, _sm, _am);
                    }
                    std::cout << "yeaah" << std::endl;
                    sf::Packet sfp = client.WaitReceive();
                    if (sfp.getData() != NULL) { //cond doesn't work
                        std::string comparator;
                        sfp >> comparator;
                        if (comparator == "new_client") {
                            /**
                            * @brief OLD CLIENT GET NEW SHIP
                            *
                            *
                            *
                            */
                            int newCliId = 0;
                            sfp >> newCliId;
                            // comment on stock les id des autres
                            entity_t newCliEntity = _ecs.spawn_entity();
                            _ecs.add_component<drawable>(newCliEntity, {_sm.Get("ship")});
                            _ecs.add_component<position>(newCliEntity, {100, 400});
                            _ecs.add_component<velocity>(newCliEntity, {2, 2});
                            _ecs.add_component<controlable>(newCliEntity, {});
                            _ecs.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                            _ecs.add_component<resizable>(newCliEntity, {2, 2});
                            _ecs.add_component<is_ship>(newCliEntity, {});
                            _ecs.add_component<collidable>(newCliEntity, {});
                            _ecs.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                            _ecs.add_component<is_ally>(newCliEntity, {true});

                        } else if (comparator == "old_client") {
                            /**
                            * @brief NEW CLIENT GET OLD SHIP
                            *
                            *
                            *
                            */

                            int amount = 0;
                            int newCliId = 0;
                            sfp >> amount;
                            for (sfp >> newCliId; amount != 0; sfp >> newCliId, amount--) {
                                if (client.GetId() != newCliId) {
                                    entity_t newCliEntity = _ecs.spawn_entity();
                                    _ecs.add_component<drawable>(newCliEntity, {_sm.Get("ship")});
                                    _ecs.add_component<position>(newCliEntity, {100, 200});
                                    _ecs.add_component<velocity>(newCliEntity, {2, 2});
                                    _ecs.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                                    _ecs.add_component<resizable>(newCliEntity, {2, 2});
                                    _ecs.add_component<is_ship>(newCliEntity, {});
                                    _ecs.add_component<collidable>(newCliEntity, {});
                                    _ecs.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                                }
                            }
                        } else if (comparator == "client_pos") {
                            /**
                             * @brief GET SHIP POSITION
                             *
                             *
                             *
                             */
                            int id = 0;
                            float x = 0;
                            float y = 0;
                            sfp >> id >> x >> y;
                            auto &positions = _ecs.get_components<position>();
                            auto &ids = _ecs.get_components<int>();
                            int i = 0;
                            for(auto &_id : ids) {
                                if (_id != std::nullopt && _id == id) {
                                    if (positions[i] != std::nullopt)
                                        _ecs.add_component<position>(_ecs.entity_from_index(i), {x, y});
                                }
                                ++i;
                            }
                        } else {
                            std::cout << "unknow type" << std::endl;
                        }
                    }
                    /**
                     * @brief SEND SHIP POSITION
                     *
                     *
                     *
                     */
                    sf::Packet packet;
                    auto &positions = _ecs.get_components<position>();

                    if (positions[4] != std::nullopt) {
                        packet << "pos_client" << client.GetId() << positions[4].value().x << positions[4].value().y;
                        if (client.getSocket().send(packet) != sf::Socket::Status::Done) {
                            std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                            exit(84);
                        }
                    }
                    User::UpdateWindowSystem(_ecs, _scenes, _window, _sm, client);
                    _window.display();
                    User::UpdatePostWindowSystem(_ecs, _scenes, _window, _am);
                }
                return 0;
            };

////////////////////////////////////////////////////////////////////////////////////////////////

            SceneManager<std::string> &GetSceneManager()
            {
                return _scenes;
            }

//            void SetScene(std::string name, bool b)
//            {
//                _scenes.Get(name).SetVisibility(b);
//            }

        private:
//dark c++ ;D
            //Auto Implement Component
            template <class T>
            struct config_extractor { // ne devrait jamais être instancié sauf erreur => gestion d'erreur
                static_assert(std::is_same_v<T, std::tuple<>>, "component_list in ComponentManager.hpp should be a tuple of Components"); // empeche la compilation si T n'est pas std::tuple<int> (ce qui ne peux jamais arriver)
                static void function(registry &r) {}
            };

            //précision
            template <class ... Components>
            struct config_extractor<std::tuple<Components...>> { // overload si T est un tuple de choses. Ne clash pas avec la def précédentes
                static void function(registry &r) {
                    (r.register_component<Components>(), ...);
                }
            };

            //
            sf::RenderWindow CreateWindow(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());

                if (ifs.good()) {
                    json file = json::parse(ifs);

                    return sf::RenderWindow(sf::VideoMode(file["window"]["width"], file["window"]["height"]),
                            std::string(file["window"]["title"]) );
                }
                std::cout << "Error: " << jsonfile << " not found" << std::endl;
                exit(84);
            }

            void InitWindow(json file)
            {
                _window.setFramerateLimit(file["window"]["framerate-limit"]);
            }

            void InitSprites(json file)
            {
                std::cout << file["sprites-path"] << std::endl;
                std::ifstream ifs(file["sprites-path"]);
                json fileSprite;

                if (ifs.good()) { //check if file exist
                    fileSprite = json::parse(ifs);
                    for (auto &it : fileSprite["sprites"]) { //get each sprite
                        std::cout << "load: " << it["name"] << it["path"] << std::endl; //debug
                        _sm.Add(it["name"], it["path"]); // add sprite to sprite manager
                    }
                } else {
                    std::cout << "sprite-path missing" << std::endl;
                    exit(84);
                }
            }

            void InitSounds(json file)
            {
                std::cout << file["sounds-path"] << std::endl;
                std::ifstream ifs(file["sounds-path"]);
                json fileSound;

                if (ifs.good()) { //check if file exist
                    fileSound = json::parse(ifs);
                    for (auto &it : fileSound["musics"]) { //get each music
                        std::cout << "load: " << it["name"] << it["path"] << std::endl; //debug
                        _mm.Add(it["name"], it["path"]); // add musics to music manager
                    }
                    for (auto &it : fileSound["audios"]) { //get each audio
                        std::cout << "load: " << it["name"] << it["path"] << std::endl; //debug
                        _am.Add(it["name"], it["path"]); // add audio to audio manager
                    }
                } else {
                    std::cout << "sound-path missing" << std::endl;
                    exit(84);
                }
            }


            void InitScenes(json file)
            {
                std::cout << file["scenes-path"] << std::endl;
                std::ifstream ifs(file["scenes-path"]);
                json fileScene;
                int sceneIds = 0;

                if (ifs.good()) {
                    fileScene = json::parse(ifs);
                    for (auto &it : fileScene["scenes"]) {
                        std::cout << it["name"] << it["path"] << std::endl;
                        _scenes.Add(it["name"], Scene(_ecs, sceneIds, it["path"]));
                        ++sceneIds;
                    }
                } else {
                    std::cout << file["scene-path"] << " is missing" << std::endl;
                    exit(84);
                }
            }

        private:
            //sfml manager
            sf::RenderWindow _window;
            sf::Event _event;

            //object manager
            //std::map<std::string, Scene> _scenes;
            registry _ecs;
            SpriteManager<std::string> _sm;

            MusicManager<std::string> _mm;
            AudioManager<std::string> _am;

            SceneManager<std::string> _scenes;

        public:
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectManager
*/

#ifndef PROJECTMANAGER_HPP_
#define PROJECTMANAGER_HPP_

#include <fstream>

//sfml
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
//json
#include "nlohmann/json.hpp"

//User
#include "User.hpp"
#include "System.hpp"

//UsefullLib
#include "SpriteManager.hpp"
#include "SceneManager.hpp"
#include "ProjectComponent.hpp"
#include "ComponentManager.hpp"

//Std
#include <tuple>
#include <type_traits> //std::is_same_v
#include <iostream>


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
            : _window(CreateWindow(jsonfile)), _sm()
            {
                _ecs.register_component<zIndex>(); //default use for scenes
                config_extractor<project_config::components_list>::function(_ecs); //sys
                config_extractor<scene_config::components_list>::function(_ecs); //sys
                config_extractor<user_config::components_list>::function(_ecs); //user
                _ecs.add_component<position>(_ecs.entity_from_index(1) , {0.f, 0.f});
                json file = json::parse(std::ifstream(jsonfile.c_str()));

                InitWindow(file);
                InitSprite(file);
                InitScene(file);
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

            int Start()
            {
                User::InitScene(_ecs, _sm, _window, _event);
                while (_window.isOpen()) {
                    User::UpdateScene(_ecs, _scenes);
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _window.close();
                            return 0;
                        }
                        User::UpdateEventSystem(_ecs, _event);
                    }
                    User::UpdateWindowSystem(_ecs, _window);
                }
                return 0;
            }

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

            void InitSprite(json file)
            {
                std::cout << file["sprite-path"] << std::endl;
                std::ifstream ifs(file["sprite-path"]);
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

            void InitScene(json file)
            {
                std::cout << file["scene-path"] << std::endl;
                std::ifstream ifs(file["scene-path"]);
                json fileScene;

                if (ifs.good()) {
                    fileScene = json::parse(ifs);
                    for (auto &it : fileScene["scenes"]) {
                        std::cout << it["name"] << it["path"] << std::endl;
                        _scenes.Add(it["name"], Scene(_ecs, it["path"]));
                    }
                } else {
                    std::cout << file["scene-path"] << " is missing" << std::endl;
                    exit(84);
                }
            }

            //sfml manager
            sf::RenderWindow _window;
            sf::Event _event;

            //object manager
            //std::map<std::string, Scene> _scenes;
            SpriteManager<std::string> _sm;
            registry _ecs;
            SceneManager<std::string> _scenes;

        public:
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

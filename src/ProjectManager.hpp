/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectManager
*/

#ifndef PROJECTMANAGER_HPP_
#define PROJECTMANAGER_HPP_

#include <fstream>

#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"

#include "System.hpp"
#include "SpriteManager.hpp"
#include "Scene.hpp"

#include "nlohmann/json.hpp"

//declare all components
#include "ComponentManager.hpp"
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
        private:
            //dark cpp
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

        public:
            ProjectManager(std::string jsonfile)
            : _window(CreateWindow(jsonfile)), _sm()
            {
                config_extractor<config::components_list>::function(_ecs);
                _ecs.add_component<position>(_ecs.entity_from_index(1) , {0.f, 0.f});
                InitWindow(jsonfile);
                InitScene(jsonfile);
                InitSprite(jsonfile);
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
                while (_window.isOpen()) {
                    _window.clear();
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _window.close();
                            return 0;
                        }
                        control_system(_ecs, _event);
                    }
                    position_system(_ecs);
                    draw_system(_ecs, _window);
                    _window.display();
                }
                return 0;
            }

        private:
            sf::RenderWindow CreateWindow(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());

                if (ifs.good()) {
                    json file = json::parse(ifs);

                    return sf::RenderWindow(sf::VideoMode(file["window"]["width"], file["window"]["height"]),
                            std::string(file["window"]["title"]) );
                }
                exit(84);
            }

            void InitWindow(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());
                json file = json::parse(ifs);

                _window.setFramerateLimit(file["window"]["framerate-limit"]);
            }

            void InitScene(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());
                json file = json::parse(ifs);

                ;
            }

            void InitSprite(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());
                json file = json::parse(ifs);

                ;
            }

            void PushScene(std::string str)
            {
                _scenes_selected.push_back(str);
            }

            void PopScene()
            {
                _scenes_selected.pop_back();
            }

            //void ControlScene(void)
            //{
            //    :
            //}

            //sfml manager
            sf::RenderWindow _window;
            sf::Event _event;

            //system manager
            std::map<std::string, Scene> _scenes;
            std::vector<std::string> _scenes_selected;


            //object manager
            SpriteManager<std::string> _sm;
            registry _ecs;
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

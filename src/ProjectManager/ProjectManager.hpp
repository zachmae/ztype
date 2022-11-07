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
#include "../User/User.hpp"
#include "../User/UserComponentManager.hpp"

//SceneManager
#include "../SceneManager/SceneManager.hpp"
#include "../SceneManager/SceneComponentManager.hpp"

//ProjectManager
#include "ProjectComponentManager.hpp"

//Manager
#include "../SpriteManager.hpp"
#include "../MusicManager.hpp"
#include "../AudioManager.hpp"

/**
 * @namespace Project
 *
 * @author perry.chouteau@epitech.eu
 */
namespace Project {

    using json = nlohmann::json;
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;
    using Music_ref = sf::Music &;
    using Sound_ref = sf::Sound &;
    using SpriteManager_ref = SpriteManager<std::string> &;

    /**
     * @brief ProjectManager
     *
     * @author perry.chouteau@epitech.eu
     */
    class ProjectManager {
        public:

            ProjectManager(std::string jsonfile)
            : _window(CreateWindow(jsonfile)), _sm(), _am(), _mm(), _userManager(jsonfile)
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

            /**
             * @brief Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int Start(std::string const &ip, unsigned short port)
            {
                _mm.play("epitomize");
                _userManager.InitScene(_ecs, _sm, _am, _scenes);
                while (_window.isOpen()) { // run the program as long as the window is open
                    _window.clear();
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _userManager.Close();
                            _window.close();
                            return 0;
                        }
                        _userManager.UpdateScene(_ecs, _scenes, _window, _event);
                        _userManager.UpdateEventSystem(_ecs, _event, _window, _sm, _am);
                    }
                    _userManager.UpdateClient(_ecs, _scenes, _sm, _am);
                    _userManager.UpdateWindowSystem(_ecs, _scenes, _window, _sm);
                    _window.display();
                    _userManager.UpdatePostWindowSystem(_ecs, _scenes, _window, _am);
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

            /**
             * @brief Config Extractor (default will make the compilation failed) [Dark C++]
             * @def the config extractor is used to extract all component need at the start of the program
             *
             * @tparam T
             */
            template <class T>
            struct config_extractor { // ne devrait jamais être instancié sauf erreur => gestion d'erreur
                static_assert(std::is_same_v<T, std::tuple<>>, "component_list in ComponentManager.hpp should be a tuple of Components"); // empeche la compilation si T n'est pas std::tuple<int> (ce qui ne peux jamais arriver)
            };

            /**
             * @brief Config Extractor (specification won't make the compilation failed) [Dark C++]
             * @def the config extractor is used to extract all component need at the start of the program
             *
             * @tparam Components
             */
            template <class ... Components>
            struct config_extractor<std::tuple<Components...>> { // overload si T est un tuple de choses. Ne clash pas avec la def précédentes
                /**
                 * @brief this function will extract all component need at the start of the program and register them in the ECS
                 *
                 * @param r
                 */
                static void function(registry &r) {
                    (r.register_component<Components>(), ...);
                }
            };

            /**
             * @brief Create Window from json file
             *
             * @param jsonfile
             * @return sf::RenderWindow
             */
            sf::RenderWindow CreateWindow(std::string jsonfile)
            {
                std::ifstream ifs(jsonfile.c_str());

                if (ifs.good()) {
                    json file = json::parse(ifs);

                    return sf::RenderWindow(sf::VideoMode(file["window"]["width"], file["window"]["height"]),
                            std::string(file["window"]["title"]) );
                }
                std::cerr << "Error: " << jsonfile << " not found" << std::endl;
                exit(84);
            }

            void InitWindow(json file)
            {
                _window.setFramerateLimit(file["window"]["framerate-limit"]);
            }

            /**
             * @brief Init Sprites from json file
             *
             * @param file
             */
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

            /**
             * @brief Init Sounds from json file
             *
             * @param file
             */
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

            /**
             * @brief Init Scenes from json file
             *
             * @param file
             */
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

            SceneManager<std::string> _scenes;

            User::UserManager _userManager;

            SpriteManager<std::string> _sm;
            MusicManager<std::string> _mm;
            AudioManager<std::string> _am;
        public:
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectManager
*/

#ifndef USER_PROJECTMANAGER_HPP_
#define USER_PROJECTMANAGER_HPP_

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
#include <nlohmann/json.hpp>

//SceneManager
#include "../SceneManager/SceneManager.hpp"
#include "../SceneManager/SceneComponentManager.hpp"

//ProjectManager
#include "../ProjectManager/ProjectManager.hpp"

//Manager
#include "../SpriteManager.hpp"
#include "../MusicManager.hpp"
#include "../AudioManager.hpp"
#include "../MusicManager.hpp"

//User
#include "Client.hpp"
#include "ClientComponentManager.hpp"

#include "Globals.hpp"
#include "Languages.hpp"

/**
 * @namespace Project
 *
 * @author perry.chouteau@epitech.eu
 */
namespace User {

    using json = nlohmann::json;
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;
    using Music_ref = sf::Music &;
    using Sound_ref = sf::Sound &;

    /**
     * @brief UserProjectManager
     *
     * @author perry.chouteau@epitech.eu
     */
    class ClientProjectManager final : public Project::ProjectManager {
        public:

            /**
             * @brief Construct a Project Manager using c++ inheritance folowing User needs !
             *
             * @param jsonfile
             */
            ClientProjectManager(std::string jsonfile)
            : ProjectManager(jsonfile), _clientManager(jsonfile), _window(CreateWindow(jsonfile)), _sm(), _am(), _mm()
            {                //User
                config_extractor<client_config::components_list>::function(_ecs); //user

                config_extractor<scene_config::components_list>::function(_ecs); //sys

                json file = json::parse(std::ifstream(jsonfile.c_str()));
                if (Globals::difficulty == 0)
                    Globals::difficulty = file["game-settings"]["difficulty"];
                InitWindow(file);
                InitSprites(file);
                InitSounds(file);
                InitScenes(file);
            };

            /**
             * @brief Destroy the User Project Manager
             *
             */
            ~ClientProjectManager() = default;

            /**
             * @brief Start our Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int Start(std::string const &ip, unsigned short port)
            {
                bool leave = false;
                _clientManager.InitScene(_ecs, _sm, _am, _mm, _scenes);
                Globals::score = 0;
                while (_window.isOpen() && !leave) { // run the program as long as the window is open
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _clientManager.Close();
                            _window.close();
                            break;
                        }
                        _clientManager.UpdateScene(_ecs, _scenes, _window, _event);
                        _clientManager.UpdateEventSystem(_ecs, _event, _window, _sm, _am);
                    }
                    if (!_window.isOpen())
                        break;
                    _clientManager.UpdateClient(_ecs, _scenes, _sm, _am);
                    _window.clear();
                    _clientManager.UpdateWindowSystem(_ecs, _scenes, _window, _sm);
                    _window.display();
                    leave = _clientManager.UpdatePostWindowSystem(_ecs, _scenes, _window, _am);
                }
                std::cout << dictionnary_language[leave ? "game_over": "bye"] << std::endl << dictionnary_language["score"] + ": " << Globals::score << std::endl;
                return 0;
            };

////////////////////////////////////////////////////////////////////////////////////////////////

        private:

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
             * @brief Init Scenes from json file
             *
             * @param file
             */
            void InitScenes(json file)
            {
                std::cout << file["scenes-path"] << std::endl;
                std::ifstream ifs(static_cast<std::string>(file["scenes-path"]));
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

            /**
             * @brief Init Sprites from json file
             *
             * @param file
             */
            void InitSprites(json file)
            {
                std::cout << file["sprites-path"] << std::endl;
                std::ifstream ifs(static_cast<std::string>(file["sprites-path"]));
                json fileSprite;

                if (ifs.good()) { //check if file exist
                    fileSprite = json::parse(ifs);
                    if (!Globals::debug_mode)
                        Globals::debug_mode =  fileSprite["debug"];
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
                std::ifstream ifs(static_cast<std::string>(file["sounds-path"]));
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


        private:
            User::ClientManager _clientManager;

            //sfml
            sf::RenderWindow _window;
            sf::Event _event;

            //manager
            SceneManager<std::string> _scenes;
            SpriteManager<std::string> _sm;
            MusicManager<std::string> _mm;
            AudioManager<std::string> _am;
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

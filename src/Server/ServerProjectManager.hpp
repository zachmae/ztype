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
#include "Server.hpp"
#include "ServerComponentManager.hpp"

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

    /**
     * @brief UserProjectManager
     *
     * @author perry.chouteau@epitech.eu
     */
    class ServerProjectManager final : public ProjectManager {
        public:

            /**
             * @brief Construct a Project Manager using c++ inheritance folowing User needs !
             *
             * @param jsonfile
             */
            ServerProjectManager(std::string jsonfile)
            : ProjectManager(jsonfile), _serverManager(jsonfile)
            {
                config_extractor<server_config::components_list>::function(_ecs); //user
            };

            /**
             * @brief Destroy the User Project Manager
             *
             */
            ~ServerProjectManager() = default;

            /**
             * @brief Start our Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int Start(std::string const &ip, unsigned short port)
            {
                while (1) {
                    break;
                }
                return 0;
            };

////////////////////////////////////////////////////////////////////////////////////////////////

        private:
            //Server functions

        private:
            Server::ServerManager _serverManager;

    };

};

#endif /* !PROJECTMANAGER_HPP_ */

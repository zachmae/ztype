/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** UserManager
*/

#ifndef USERMANAGER_HPP_
    #define USERMANAGER_HPP_

    #include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

    #include "../ProjectManager/ProjectComponent.hpp"
    #include "../SceneManager/SceneComponent.hpp"
    #include "../SceneManager/SceneManager.hpp"

    #include "Systems/ServerSystem.hpp"
    #include "Systems/System.hpp"
    #include "Network/Client.hpp"

    #include "ServerComponent.hpp"


    #include "AudioManager.hpp"
    #include "SpriteManager.hpp"
    #include "MusicManager.hpp"

    #include "sfml_ref.hpp"

/**
 * @brief namespace User
 *
 * @author perry.chouteau@epitech.eu
 */
namespace User {

    /**
     * @class UserManager
     *
     * @brief class used to manage user
     *
     * @author perry.chouteau@epitech.eu
     */
    class ServerManager final {
        public:
            /**
             * @brief Construct a new User Manager object
             * init Client
             *
             */
            ServerManager(std::string jsonfile)
            : _server(getNetwork(jsonfile))
            {

            }

            /**
             * @brief Destroy UserManager
             *
             */
            ~ServerManager() = default;

            UpdateServer();
            UpdateClients(Registry_ref registry);


        private:

            /**
             * @brief Get the Network info from json file
             *
             * @param path
             * @return std::pair<std::string, int>
             */
            int getNetwork(std::string path)
            {
                std::ifstream ifs(path.c_str());

                if (ifs.good()) {
                    json file = json::parse(ifs);

                    return file["network"]["port"];
                }
                std::cout << "Error: " << path << " not found" << std::endl;
                exit(84);
            }

            Server _server;
    };
}

#endif /* !USERMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** UserManager
*/

#ifndef USERMANAGER_HPP_
    #define USERMANAGER_HPP_

    #include "../SceneManager/SceneManager.hpp"
    #include "../SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

    #include "ClientComponent.hpp"
    #include "../SceneManager/SceneComponent.hpp"
    #include "../SceneManager/SceneManager.hpp"

    #include "Systems/ClientSystem.hpp"
    #include "Systems/System.hpp"
    #include "Scenes/Game/Game.hpp" // WHAT THE FUCK

    #include "Network/Client.hpp"

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
    class ClientManager final {
        public:
            /**
             * @brief Construct a new User Manager object
             * init Client
             *
             */
            ClientManager(std::string jsonfile)
            : _client(getNetwork(jsonfile).first, getNetwork(jsonfile).second)
            {

            }

            /**
             * @brief Destroy UserManager
             *
             */
            ~ClientManager() = default;

            /**
             * @brief init scene
             *
             * @deprecated may be replace by a json file automation
             * @param r
             * @param sm
             * @param am
             * @param scene
             */
//            [[deprecated]]
            void InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm, SceneManager_ref<std::string> scene);

            /**
             * @brief Update the User Manager object
             *
             * @tparam Key
             * @param reg
             * @param window
             * @param event
             */
            template <typename Key>
            void UpdateScene(Registry_ref reg, SceneManager<Key> &, sf::RenderWindow &window, sf::Event &event);

            /**
             * @brief When Project is closing call this function to let the user act as he want
             *
             */
            void Close();

            /**
             * @brief Update Event System
             *
             * @tparam Key
             * @param reg
             * @param event
             * @param window
             * @param sm
             * @param am
             */
            template<typename Key>
            void UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am);

            /**
             * @brief Update Client
             *
             * @tparam Key
             * @param reg
             * @param scenes
             * @param _sm
             * @param am
             */
            template<typename Key>
            void UpdateClient(Registry_ref reg, SceneManager_ref<std::string> scenes, SpriteManager_ref<Key> _sm, AudioManager_ref<Key> am);

            /**
             * @brief Update Window System
             *
             * @tparam Key
             * @param reg
             * @param scene
             * @param window
             * @param sm
             */
            template<typename Key>
            void UpdateWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, SpriteManager_ref<Key> sm);

            /**
             * @brief Update Post Window System
             *
             * @tparam Key
             * @param reg
             * @param scene
             * @param window
             * @param am
             */
            template<typename Key>
            void UpdatePostWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, AudioManager_ref<std::string> am);

        private:

            /**
             * @brief Get the Network info from json file
             *
             * @param path
             * @return std::pair<std::string, int>
             */
            std::pair<std::string, int> getNetwork(std::string path)
            {
                std::ifstream ifs(path.c_str());

                if (ifs.good()) {
                    json file = json::parse(ifs);

                    return std::pair<std::string, int>(file["network"]["ip"], file["network"]["port"]);
                }
                std::cout << "Error: " << path << " not found" << std::endl;
                exit(84);
            }

            Client _client;
    };
}

#endif /* !USERMANAGER_HPP_ */

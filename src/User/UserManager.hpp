/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** UserManager
*/

#ifndef USERMANAGER_HPP_
    #define USERMANAGER_HPP_

    #include "SceneManager/SceneManager.hpp"
    #include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

    #include "ProjectManager/ProjectComponent.hpp"
    #include "UserComponent.hpp"
    #include "SceneManager/SceneComponent.hpp"
    #include "SceneManager/SceneManager.hpp"

    #include "User/Systems/UserSystem.hpp"
    #include "User/Systems/System.hpp"
    #include "User/Scenes/Game/Game.hpp" // WHAT THE FUCK

    #include "Network/Client.hpp"

    #include "AudioManager.hpp"
    #include "SpriteManager.hpp"

    #include "sfml_ref.hpp"

namespace User {

    class UserManager {
        public:
            /**
             * @brief Construct a new User Manager object
             * init Client
             *
             */
            UserManager(std::string jsonfile)
            : _client(getNetwork(jsonfile).first, getNetwork(jsonfile).second)
            {

            }

            ~UserManager() = default;

            [[deprecated]]
            void InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, AudioManager_ref<std::string> am, SceneManager_ref<std::string> scene);

            template <typename Key>
            void UpdateScene(Registry_ref reg, SceneManager<Key> &scene);

            void Close();

            template<typename Key>
            void UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am);

            template<typename Key>
            void UpdateClient(Registry_ref reg, SceneManager_ref<std::string> scenes, SpriteManager_ref<Key> _sm, AudioManager_ref<Key> am);

            template<typename Key>
            void UpdateWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, SpriteManager_ref<Key> sm);

            template<typename Key>
            void UpdatePostWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, AudioManager_ref<std::string> am);

        private:

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

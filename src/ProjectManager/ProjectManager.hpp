/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectManager
*/

#ifndef PROJECTMANAGER_HPP_
#define PROJECTMANAGER_HPP_

//Std
#include <tuple>
#include <type_traits> //std::is_same_v
#include <iostream>

//User
#include "../User/User.hpp"
#include "../User/UserComponentManager.hpp"

//ProjectManager
#include "ProjectComponentManager.hpp"

/**
 * @namespace Project
 *
 * @author perry.chouteau@epitech.eu
 */
namespace Project {

    /**
     * @brief ProjectManager
     *
     * @author perry.chouteau@epitech.eu
     */
    class ProjectManager {
        public:

            ProjectManager(std::string jsonfile)
            : _userManager(jsonfile)
            {
                config_extractor<project_config::components_list>::function(_ecs); //sys
                config_extractor<user_config::components_list>::function(_ecs); //user
            };

            ~ProjectManager() = default;

            /**
             * @brief Client
             *
             * @param ip
             * @param port
             * @return int
             */
            virtual int Start(std::string const &ip, unsigned short port) = 0;

////////////////////////////////////////////////////////////////////////////////////////////////

        protected:

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

        protected:
            registry _ecs;

            User::UserManager _userManager;

        public:
    };

};

#endif /* !PROJECTMANAGER_HPP_ */

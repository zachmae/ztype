/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Scene
*/

#include <map>
#include <vector>
#include "Ecs.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using Registry_ref = registry &;

//using Scene_ref = Scene &;
////using Scenes = std::vector<Scene>;
////using Scenes_ref = Scenes &;

class Scene {
    public:
//        Scene &operator=(const Scene &other)
//        {
//            this->_ecs = other._ecs;
//            return *this;
//        }
//
//        Scene(const Scene &) = default;
//        ~Scene() = default;
        Scene(Registry_ref reg, std::string path)
        : _ecs(reg)
        {
            std::ifstream ifs(path);
            json scenefile;
            if (ifs.good()) {
                scenefile = json::parse(ifs);
                std::cout << scenefile << std::endl;
                for (auto &entity : scenefile["entities"]) {
                    _entities.push_back(_ecs.spawn_entity());
                }
                std::cout << "Scene loaded" << std::endl;
            } else {
                std::cout << "Scene not loaded" << std::endl;
            }
            std::cout << "Scene created" << std::endl;
            //load entity from json
        }

        Registry_ref _ecs;
        std::vector<entity_t> _entities;
};
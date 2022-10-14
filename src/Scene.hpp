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
#include "SceneComponent.hpp"

using json = nlohmann::json;
using Registry_ref = registry &;

//using Scene_ref = Scene &;
////using Scenes = std::vector<Scene>;
////using Scenes_ref = Scenes &;

#ifndef SCENE_HPP_
    #define SCENE_HPP_

class Scene {
    public:
        Scene(Registry_ref reg, std::string path)
        : _ecs(reg)
        {
            std::ifstream ifs(path);
            json scenefile;
            if (ifs.good()) {
                scenefile = json::parse(ifs);
                std::cout << scenefile << std::endl;
                //for (auto &entity : scenefile["entities"]) {
                //    entity_t e = _ecs.spawn_entity();
                //    _entities.push_back(e);
                //    std::cout << "not-used"<< entity << std::endl;
                //    std::cout << "\tentity: " << e._idx << std::endl;
                //}
                std::cout << "Scene loaded" << std::endl;
            } else {
                std::cout << "Scene not loaded" << std::endl;
            }
            std::cout << "Scene created" << std::endl;

            //load entity from json
            SceneVisibility(false);
        }

        void SceneVisibility(bool b)
        {
            for (auto &entity : _entities)
                _ecs.add_component<visible>(entity, {b});
            std::cout << "Scene set to " << ((b) ? "visible" : "invisible") << std::endl;
        }

    private:
        Registry_ref _ecs;
        std::vector<entity_t> _entities;
};

#endif /* !SCENE_HPP_ */
/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Scene
*/

#include <fstream>

#include <map>
#include <vector>
#include "Ecs.hpp"
#include "nlohmann/json.hpp"
#include "SceneComponent.hpp"
#include "SpriteManager.hpp"

using json = nlohmann::json;
using Registry_ref = registry &;
using Event_ref = sf::Event &;
using Window_ref = sf::RenderWindow &;
//using Scene_ref = Scene &;
////using Scenes = std::vector<Scene>;
////using Scenes_ref = Scenes &;

#ifndef SCENE_HPP_
    #define SCENE_HPP_

class Scene {
    public:
        Scene(Registry_ref reg, int sceneId, std::string path)
        : _ecs(reg), _id(sceneId), _zIndex(0)
        {
            std::ifstream ifs(path);
            json file;
            if (ifs.good()) {
                file = json::parse(ifs);
                std::cout << file << std::endl;
                //for (auto &entity : file["entities"]) {
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
        }

        entity_t SpawnEntity(entity_t e)
        {
            entity_t ent = _ecs.spawn_entity();
            _ecs.add_component<SceneId>(ent, {_id});
            return ent;
        }

        void SetZIndex(int zIndex)
        {
            _zIndex = zIndex;
        }

        int GetZIndex() const
        {
            return _zIndex;
        }

        int GetId() const
        {
            return _id;
        }

    private:
        Registry_ref _ecs;
        int _zIndex;
        int _id;
};

#endif /* !SCENE_HPP_ */
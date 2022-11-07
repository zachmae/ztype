/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Scene
*/

#include <fstream>
#include <map>
#include <vector>

#include "../nlohmann/json.hpp"

#include "../ProjectManager/Ecs.hpp"
#include "SceneComponent.hpp"

#ifndef SCENE_HPP_
    #define SCENE_HPP_

using json = nlohmann::json;
using Registry_ref = registry &;

/**
 * @class Scene
 *
 * @brief used in SceneManager
 *
 * @author perry.chouteau@epitech.eu
 */
class Scene {

    using Scene_ref = Scene &;

    public:

        Scene() = delete;
        /**
         * @brief Construct a new Scene object
         *
         * @param reg
         * @param sceneId
         * @param path
         */
        Scene(Registry_ref reg, int sceneId, std::string path)
        : _ecs(reg)
        {
            std::ifstream ifs(path);
            json file;

            _id = sceneId;
            _zIndex = 0;
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

        /**
         * @brief Spawn an entity like in Ecs but with a sceneId
         *
         * @return entity_t
         */
        entity_t SpawnEntity()
        {
            entity_t ent = _ecs.spawn_entity();
            _ecs.add_component<SceneId>(ent, {_id});
            return ent;
        }

        /**
         * @brief Set the Z Index of the scene
         *
         * @param zIndex
         * @return int
         */
        int SetZIndex(int zIndex)
        {
            _zIndex = zIndex;
            return _zIndex;
        }

        /**
         * @brief Get the Z Index of the scene
         *
         * @param zIndex
         * @return int
         */
        int GetZIndex() const
        {
            return _zIndex;
        }

        /**
         * @brief Get the Id of the scene
         *
         * @return int
         */
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
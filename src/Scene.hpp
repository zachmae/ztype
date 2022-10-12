/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** Scene
*/

#include <map>
#include <vector>

//#include "Component.hpp"
//#include "System.hpp"
//#include "SpriteManager.hpp"

class Scene;

using Scene_ref = Scene &;
using Scenes = std::vector<Scene>;
using Scenes_ref = Scenes &;

class Scene {
    using Registry_ref = registry &;

    public:
        Scene() = delete;
        ~Scene() = default;
        //Scene(Window_ref window, Event_ref event, Registry_ref registry, SpriteManager_ref<std::string> sm);
/*        Scene(Registry_ref reg, GameStd::SpriteManager<std::string> &sm, std::string jsonfile)
        : _reg(reg), _sm(sm)
        {
            ;
        }*/

    private:
        registry &_reg;
        GameStd::SpriteManager<std::string> &_sm;
};

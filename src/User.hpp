/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

// edit function
namespace User {

    [[deprecated]]
    void InitScene(Registry_ref ecs, SpriteManager_ref<std::string> sm, Window_ref window, Event_ref event)
    {
        Registry_ref _ecs = ecs;
        SpriteManager_ref<std::string> _sm = sm;
        Event_ref _event = event;
        ecs = _ecs;
        sm = _sm;
        window.isOpen();
        event = _event;

        //init what you want but it's deprecated cause you can do it using Component & ComponentManager & editing assets/conf/...
    }

    void UpdateScene(SceneManager<std::string> &scene)
    {
        //all scene update
        for (auto &s : scene.GetKeysUsed()) {
            scene.Get(s).SceneVisibility(true); //error
        }
    }

    void UpdateEventSystem(Registry_ref reg, Event_ref event)
    {
        //all event system
        Registry_ref _reg = reg;
        Event_ref _event = event;

        reg = _reg;
        event = _event;
    }

    void UpdateWindowSystem(Registry_ref reg, Window_ref window)
    {
        //all system
        Registry_ref _reg = reg;

        reg = _reg;
        window.isOpen();
    }
}
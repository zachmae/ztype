/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager.hpp"

// edit function
namespace User {
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
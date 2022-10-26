/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used
#include "ProjectComponent.hpp"
#include "Component.hpp"
#include "System.hpp"

// edit function
namespace User {

    [[deprecated]]
    void InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, Window_ref window, Event_ref event)
    {
        entity_t e = r.spawn_entity();
        r.add_component<drawable>(e, {sm.Get("ship")});
        r.add_component<position>(e, {0, 0});
        r.add_component<velocity>(e, {0, 0});
        r.add_component<contralable>(e, {});
        r.add_component<visible>(e, {false});

        //init what you want but it's deprecated cause you can do it using Component & ComponentManager & editing assets/conf/...
    }

    void UpdateScene(Registry_ref reg, SceneManager<std::string> &scene)
    {
    }

    bool CloseEvent(Event_ref event, Window_ref window)
    {
        if (event.key.code == sf::Keyboard::Escape) {
            window.close();
            return true;
        }
        return false;
    }

    void UpdateEventSystem(Registry_ref reg, Event_ref event)
    {
        control_system(reg, event);
    }

    void UpdateWindowSystem(Registry_ref reg, Window_ref window)
    {
        //all system
        position_system(reg);
        draw_system(reg, window);
    }

}
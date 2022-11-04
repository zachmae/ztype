/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** User
*/

#include "SceneManager/SceneManager.hpp"
#include "SpriteManager.hpp" // add init scene deprecated cause shouldn't be used

#include "ProjectManager/ProjectComponent.hpp"
#include "UserComponent.hpp"
#include "SceneManager/SceneComponent.hpp"
#include "SceneManager/SceneManager.hpp"

#include "UserSystem.hpp"
#include "User/Systems/System.hpp"

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

// edit function
namespace User {

    [[deprecated]]
    void InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, SceneManager_ref<std::string> scene, Client & client)
    {
        scene.Get("tutorial").SetZIndex(-1);
        scene.Get("game").SetZIndex(-1);
        scene.Get("menu").SetZIndex(-1);
        scene.Get("loading").SetZIndex(-1);
        scene.Get("start").SetZIndex(-1);
        scene.Get("gameover").SetZIndex(-1);
        scene.Get("win").SetZIndex(-1);

        entity_t e1 = scene.Get("tutorial").SpawnEntity();
        scene.Get("tutorial").SetZIndex(1);
        r.add_component<drawable>(e1, {sm.Get("background")});
        r.add_component<position>(e1, {0, 0});
        r.add_component<velocity>(e1, {0, 0});
        r.add_component<visible>(e1, {true});

        entity_t e2 = scene.Get("loading").SpawnEntity();
        scene.Get("loading").SetZIndex(3);
        r.add_component<drawable>(e2, {sm.Get("ship")});
        r.add_component<position>(e2, {0, 0});
        r.add_component<velocity>(e2, {0, 0});
        r.add_component<controlable>(e2, {});
        r.add_component<visible>(e2, {true});
        std::cout << "I'm there" << std::endl;
        r.add_component<int>(e2, client.GetId()); // GET THE ID OF THE SHIP new client id
        std::cout << "I'm not there" << std::endl;
        r.add_component<controlable>(e2, {});
        r.add_component<is_ally>(e2, {true});

        entity_t e3 = scene.Get("game").SpawnEntity();
        scene.Get("game").SetZIndex(2);
        r.add_component<drawable>(e3, {sm.Get("enemy")});
        r.add_component<position>(e3, {0, 0});
        r.add_component<velocity>(e3, {0, 0});
        r.add_component<visible>(e3, {true});
    }

    template <typename Key>
    void UpdateScene(Registry_ref reg, SceneManager<Key> &scene)
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

    template<typename Key>
    void UpdateEventSystem(Registry_ref reg, Event_ref event, Window_ref window, SpriteManager_ref<Key> sm, AudioManager_ref<Key> am)
    {
        control_system(reg, event, sm, am);
    }

    template<typename Key>
    void UpdateWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, SpriteManager_ref<Key> sm, Client &client)
    {
        //all system
        ennemy_system(reg, sm, window);
        boss_magic_system(reg, sm, window);
        position_system(reg, window, client);
        draw_system(reg, window);
        displayscene_system(reg, scene, window);
        position_system(reg);

//        draw_system(reg, window);

    }

    template<typename Key>
    void UpdatePostWindowSystem(Registry_ref reg, SceneManager_ref<Key> scene, Window_ref window, AudioManager_ref<std::string> am)
    {
        collision_system(reg, am);
        remove_out_of_screen_system(reg, window);
    }

}
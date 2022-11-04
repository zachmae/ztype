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
#include "User/Game/init.cpp" // WHAT THE FUCK

#include "Network/Client.hpp"

#include "AudioManager.hpp"
#include "SpriteManager.hpp"

#include "sfml_ref.hpp"

/**
 * @brief namespace User
 *
 */
namespace User {

    /**
     * @brief
     *
     * @param r
     * @param sm
     * @param scene
     * @param client
     */
    [[deprecated]]
    void InitScene(Registry_ref r, SpriteManager_ref<std::string> sm, AudioManager_ref<std::string> am, SceneManager_ref<std::string> scene, Client & client)
    {
        scene.Get("tutorial").SetZIndex(-1);
        scene.Get("game").SetZIndex(-1);
        scene.Get("menu").SetZIndex(-1);
        scene.Get("loading").SetZIndex(-1);
        scene.Get("settings").SetZIndex(-1);
        scene.Get("lose").SetZIndex(-1);
        scene.Get("win").SetZIndex(-1);

        std::cout << "InitScene" << std::endl;
        background_generation(r, sm, scene, "background_back", -0.1f);
        std::cout << "bg 1 done" << std::endl;
        background_generation(r, sm, scene, "background_stars", -0.2f);
        background_generation(r, sm, scene, "background_planets_back", -0.5f);
        background_generation(r, sm, scene, "background_planets_front", -0.8f);
        std::cout << "InitScene mid" << std::endl;
        ship_generation(r, sm, scene, am, "ship", true);

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
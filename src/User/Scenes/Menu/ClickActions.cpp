/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ClickActions
*/

#include "ClickActions.hpp"

void back_to_game(SceneManager_ref<std::string> scene)
{
    // SceneManager_ref<std::string> scene(p...);

    scene.Get("menu").SetZIndex(-1);
    // std::cout << "                          TEST" << std::endl;
}

void exit_game(SceneManager_ref<std::string> scene)
{
    scene.Get("menu").SetZIndex(-1);
    scene.Get("game").SetZIndex(-1);
}

void pop_settings(SceneManager_ref<std::string> scene)
{
    if (scene.Get("menu").GetZIndex() == 2)
        scene.Get("game").SetZIndex(-1);
    scene.Get("menu").SetZIndex(2);
}
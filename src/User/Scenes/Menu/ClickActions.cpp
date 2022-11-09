/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ClickActions
*/

#include "ClickActions.hpp"

void test_menu(SceneManager_ref<std::string> scene)
{
    // SceneManager_ref<std::string> scene(p...);

    scene.Get("menu").SetZIndex(-1);
    std::cout << "                          TEST" << std::endl;
}
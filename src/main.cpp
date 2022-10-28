/*
** EPITECH PROJECT, 2022
** rtype
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** main
*/

#include <SFML/Window.hpp>
#include "ProjectManager/ProjectManager.hpp"

int main()
{
    //! make the constructeur use a ardcoded json filepath
    GameStd::ProjectManager pm("assets/conf/project-manager.json");
//    GameStd::GameManager manager(window, event);
    return pm.Start();
//    return manager.run();
}
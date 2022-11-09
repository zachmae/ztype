/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SceneComponent
*/

#include "SceneComponent.hpp"
#include <tuple>

#ifndef SCENECOMPONENTMANAGER_HPP_
#define SCENECOMPONENTMANAGER_HPP_

/**
 * @brief scene config listing all components used by scenes
 *
 * @author perry.chouteau@epitech.eu
 */
struct scene_config {
    using components_list = std::tuple<SceneId>;
};

#endif /* !SCENECOMPONENTMANAGER_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SceneComponent
*/

#ifndef SCENECOMPONENT_HPP_
#define SCENECOMPONENT_HPP_

struct zIndex {
    bool _zIndex;
};

struct scene_config {
    using components_list = std::tuple<zIndex>;
};

#endif /* !SCENECOMPONENT_HPP_ */

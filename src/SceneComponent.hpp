/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SceneComponent
*/

#ifndef SCENECOMPONENT_HPP_
#define SCENECOMPONENT_HPP_

struct visible {
    bool _visible;
};

struct sys_config {
    using components_list = std::tuple<visible>;
};

#endif /* !SCENECOMPONENT_HPP_ */

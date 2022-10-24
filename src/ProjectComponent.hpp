/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ProjectComponent
*/

#ifndef PROJECTCOMPONENT_HPP_
#define PROJECTCOMPONENT_HPP_

struct visible {
    bool _visible;
};

struct project_config {
    using components_list = std::tuple<visible>;
};

#endif /* !PROJECTCOMPONENT_HPP_ */

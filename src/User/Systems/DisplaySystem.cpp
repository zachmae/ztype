/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DisplaySystem
*/

#include "System.hpp"

void User::draw_system(registry &r, Window_ref w)
{
    auto &drawables = r.get_components<drawable>();
    auto &positions = r.get_components<position>();
    auto &animation_adaptatives = r.get_components<struct animation_adaptative>();
    auto &resizables = r.get_components<struct resizable>();

    animation_basic_system(r);
    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i]) {
            if (i < positions.size() && positions[i])
                drawables[i]->sprite.setPosition(positions[i]->x, positions[i]->y);
            if (i < animation_adaptatives.size() && animation_adaptatives[i])
                drawables[i]->sprite.setTextureRect(animation_adaptatives[i]->rect);
            if (i < resizables.size() && resizables[i])
                drawables[i]->sprite.setScale(resizables[i]->x, resizables[i]->y);
            w.draw(drawables[i]->sprite);
        }
    }
}
/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "System.hpp"

void GameStd::animation_basic_system(registry &r)
{
    auto &animations = r.get_components<struct animation_basic>();
    auto &drawables = r.get_components<struct drawable>();

    for (size_t i = 0; i < animations.size() && i < drawables.size(); ++i) {
        if (animations[i] && drawables[i]) {
            animations[i]->frame_current = (animations[i]->frame_current + 1) % animations[i]->frame_max;
            animations[i]->rect.left = animations[i]->frame_current * animations[i]->frame_size;
            drawables[i]->sprite.setTextureRect(animations[i]->rect);
        }
    }
}

void GameStd::animate_ship_system(registry &r, size_t entity_index, int key_code)
{
    auto &animations = r.get_components<struct animation_adaptative>();

    if (key_code == sf::Keyboard::Z) {
        animations[entity_index]->rect.left += static_cast<int>(166.0 * 0.2);
        if (animations[entity_index]->rect.left >= 166 * 0.8)
            animations[entity_index]->rect.left = static_cast<int>(166.0 * 0.8);
    } else if (key_code == sf::Keyboard::S) {
        animations[entity_index]->rect.left -= static_cast<int>(166.0 * 0.2);
        if (animations[entity_index]->rect.left < 0)
            animations[entity_index]->rect.left = 0;
    } else if (key_code == sf::Keyboard::Q || key_code == sf::Keyboard::D)
        animations[entity_index]->rect.left = static_cast<int>(166.0 * 0.4);
}

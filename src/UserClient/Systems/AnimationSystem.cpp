/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AnimationSystem
*/

#include "System.hpp"

void User::animation_basic_system(registry &r)
{
    static std::vector<std::chrono::steady_clock::time_point> animation_timing = {};
    auto &animations = r.get_components<struct animation_basic>();
    size_t old_size = animation_timing.size();
    animation_timing.resize(animations.size());
    auto &drawables = r.get_components<struct drawable>();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

    for (size_t i = old_size; i < animations.size(); ++i) {
        if (!animations[i] || !drawables[i])
            continue;
        animations[i]->frame_current = (animations[i]->frame_current + 1) % animations[i]->frame_max;
        animations[i]->rect.left = animations[i]->frame_current * animations[i]->frame_size;
        drawables[i]->sprite.setTextureRect(animations[i]->rect);
        animation_timing[i] = current_time;
    }
    for (size_t i = 0; i < animations.size() && i < drawables.size(); ++i) {
        if (animations[i] && drawables[i]) {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(current_time - animation_timing[i]) >= std::chrono::milliseconds(static_cast<int>(animations[i]->frame_time * 1000))) {
                animations[i]->frame_current = (animations[i]->frame_current + 1) % animations[i]->frame_max;
                animations[i]->rect.left = animations[i]->frame_current * animations[i]->frame_size;
                drawables[i]->sprite.setTextureRect(animations[i]->rect);
                animation_timing[i] = current_time;
            }
        }
    }

}

void User::animate_ship_system(registry &r, size_t entity_index, int key_code)
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

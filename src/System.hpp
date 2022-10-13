/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** System
*/

#include <optional>
#include "Ecs.hpp"
#include "Component.hpp"
#include "SpriteManager.hpp"

namespace GameStd {

    inline bool is_ship_out_system(std::optional<position> pos, std::optional<velocity> vel, Window_ref w)
    {
        if (pos->x + vel->x  < 0)
            return true;
        if (pos->x + vel->x > w.getSize().x - 48)
            return true;
        if (pos->y + vel->y < 0)
            return true;
        if (pos->y + vel->y > w.getSize().y - 32)
            return true;
        return false;
    }

    inline void position_system(registry &r, Window_ref w)
    {
        auto &positions = r.get_components<struct position>();
        auto &controlables = r.get_components<struct controlable>();
        auto &velocities = r.get_components<struct velocity>();
        auto &is_ship = r.get_components<struct is_Ship>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            if (i < is_ship.size() && is_ship[i] && is_ship_out_system(positions[i], velocities[i], w))
                continue;
            if (positions[i] && velocities[i]) {
                positions[i]->x += velocities[i]->x;
                positions[i]->y += velocities[i]->y;
            }
        }
        for (size_t i = 0; i < velocities.size() && i < controlables.size(); ++i) {
            if (velocities[i] && controlables[i]) {
                velocities[i]->y = 0;
                velocities[i]->x = 0;
            }
        }
    }

    inline void animation_basic_system(registry &r)
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

    inline void bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager)
    {
        entity_t bullet = r.spawn_entity();
        r.add_component<drawable>(bullet, {_spriteManager.Get("bullet")});
        r.add_component<position>(bullet, {src_x + 32, src_y + 8});
        r.add_component<velocity>(bullet, {10, 0});
        r.add_component<animation_basic>(bullet, {sf::IntRect(0, 34, 50, 17), 0, 8, 50, 0.1});
    }

    inline void animate_ship_system(registry &r, int entity_index, int key_code)
    {
        auto &animations = r.get_components<struct animation_adaptative>();

        if (key_code == sf::Keyboard::Z) {
            animations[entity_index]->rect.left += 166 * 0.2;
            if (animations[entity_index]->rect.left >= 166 * 0.8)
                animations[entity_index]->rect.left = 166 * 0.8;
        } else if (key_code == sf::Keyboard::S) {
            animations[entity_index]->rect.left -= 166 * 0.2;
            if (animations[entity_index]->rect.left < 0)
                animations[entity_index]->rect.left = 0;
        } else if (key_code == sf::Keyboard::Q || key_code == sf::Keyboard::D) {
            animations[entity_index]->rect.left = 166 * 0.4;
        }
    }

    inline void control_system(registry &r, Event_ref e, SpriteManager<std::string> _spriteManager)
    {
        auto &controllables = r.get_components<controlable>();
        auto &velocities = r.get_components<velocity>();
        auto &positions = r.get_components<position>();
        auto &is_ship = r.get_components<is_Ship>();

        for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
            if (velocities[i] && controllables[i] && e.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                    velocities[i]->y = -10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    velocities[i]->y = 10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                    velocities[i]->x = -10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    velocities[i]->x = 10;
                } if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    bullet_creation_system(r, positions[i]->x, positions[i]->y, _spriteManager);
                }
                if (i < is_ship.size() && is_ship[i])
                    animate_ship_system(r, i, e.key.code);
            }
        }
    }

    inline void remove_out_of_screen_system(registry &r, Window_ref w)
    {
        auto &positions = r.get_components<position>();
        auto &drawables = r.get_components<drawable>();

        for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
            if (positions[i] && drawables[i]) {
                if (positions[i]->x > w.getSize().x || positions[i]->x < 0 || positions[i]->y > w.getSize().y || positions[i]->y < 0) {
                    r.kill_entity(r.entity_from_index(i));
                }
            }
        }
    }

    inline void draw_system(registry &r, Window_ref w)
    {
        auto &drawables = r.get_components<drawable>();
        auto &positions = r.get_components<position>();
        auto &animation_adaptatives = r.get_components<struct animation_adaptative>();
        auto &resizables = r.get_components<struct resizable>();

        animation_basic_system(r);
        w.clear(sf::Color::Black);
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
        w.display();
    }
}
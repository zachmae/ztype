/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** System
*/

#include <optional>
#include <chrono>
#include "Ecs.hpp"
#include "Component.hpp"
#include "SpriteManager.hpp"

namespace GameStd {

    inline bool is_ship_out_system(std::optional<position> pos, std::optional<velocity> vel, Window_ref w)
    {
        if (pos->x + vel->x  < 0)
            return true;
        if (pos->x + vel->x > w.getSize().x - 48.0)
            return true;
        if (pos->y + vel->y < 0)
            return true;
        if (pos->y + vel->y > w.getSize().y - 32.0)
            return true;
        return false;
    }

    inline void position_system(registry &r, Window_ref w)
    {
        auto &positions = r.get_components<struct position>();
        auto &controlables = r.get_components<struct controlable>();
        auto &velocities = r.get_components<struct velocity>();
        auto &are_ships = r.get_components<struct is_ship>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            if (i < are_ships.size() && are_ships[i] && is_ship_out_system(positions[i], velocities[i], w))
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
        static clock_t last_time = clock();
        clock_t current_time = clock();
        float elapsed_time = ((float)(current_time - last_time) / CLOCKS_PER_SEC) * 60;

        if (elapsed_time < 1)
            return;
        entity_t bullet = r.spawn_entity();
        r.add_component<drawable>(bullet, {_spriteManager.Get("bullet")});
        r.add_component<position>(bullet, {src_x + 64, src_y + 8});
        r.add_component<velocity>(bullet, {10, 0});
        r.add_component<animation_basic>(bullet, {sf::IntRect(0, 34, 50, 17), 0, 8, 50, 0.1f});
        r.add_component<collidable>(bullet, {});
        last_time = current_time;
    }

    inline void animate_ship_system(registry &r, size_t entity_index, int key_code)
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
        } else if (key_code == sf::Keyboard::Q || key_code == sf::Keyboard::D) {
            animations[entity_index]->rect.left = static_cast<int>(166.0 * 0.4);
        }
    }

    inline void ennemy_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w)
    {
        static clock_t last_time = clock();
        clock_t current_time = clock();
        float elapsed_time = (static_cast<float>(current_time - last_time) / CLOCKS_PER_SEC) * 60;

        if (elapsed_time < 2)
            return;
        entity_t ennemy = r.spawn_entity();
        r.add_component<drawable>(ennemy, {_spriteManager.Get("ennemy")});
        r.add_component<position>(ennemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 64))});
        r.add_component<velocity>(ennemy, {-3, 0});
        r.add_component<animation_adaptative>(ennemy, {sf::IntRect(0, 0, 64, 64), 0, 0, 0.5f});
        r.add_component<collidable>(ennemy, {});
        last_time = current_time;
    }

    inline void collision_system(registry &r)
    {
        auto &collidables = r.get_components<struct collidable>();
        auto &drawables = r.get_components<struct drawable>();

        for (unsigned int idx_1 = 0; idx_1 < collidables.size() && idx_1 < drawables.size(); ++idx_1) {
            for (unsigned int idx_2 = idx_1 + 1; idx_2 < collidables.size(); ++idx_2) {
                if (collidables[idx_1] && collidables[idx_2] && drawables[idx_1] && drawables[idx_2]) {
                    if (drawables[idx_1]->sprite.getGlobalBounds().intersects(drawables[idx_2]->sprite.getGlobalBounds())) {
                        r.kill_entity(r.entity_from_index(idx_1));
                        r.kill_entity(r.entity_from_index(idx_2));
                    }
                }
            }
        }
    }

    inline void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager)
    {
        auto &controllables = r.get_components<controlable>();
        auto &velocities = r.get_components<velocity>();
        auto &positions = r.get_components<position>();
        auto &are_ships = r.get_components<is_ship>();

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
                if (i < are_ships.size() && are_ships[i])
                    animate_ship_system(r, i, e.key.code);
            }
        }
    }

    inline void remove_out_of_screen_system(registry &r, Window_ref w)
    {
        auto &positions = r.get_components<position>();
        auto &drawables = r.get_components<drawable>();
        auto &are_backgrounds = r.get_components<is_background>();

        for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i) {
            if (positions[i] && drawables[i] && !are_backgrounds[i]) {
                if (positions[i]->x > static_cast<float>(w.getSize().x) || positions[i]->x < 0
                    || positions[i]->y > static_cast<float>(w.getSize().y) || positions[i]->y < 0) {
                    r.kill_entity(r.entity_from_index(i));
                }
            }
            if (positions[i] && drawables[i] && are_backgrounds[i]) {
                if (positions[i]->x < -static_cast<float>(w.getSize().x))
                    positions[i]->x = 0;
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
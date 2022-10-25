/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EventSystem
*/

#include "System.hpp"

void GameStd::control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager)
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

void GameStd::ennemy_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w)
{
    int bosses = 0;
    auto &are_bosses = r.get_components<is_boss>();
    for (size_t i = 0; i < are_bosses.size(); ++i) {
        if (are_bosses[i])
            bosses++;
    }
    if (bosses)
        return;
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::seconds time_span = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time);
    if (time_span < std::chrono::seconds(2))
        return;
    entity_t ennemy = r.spawn_entity();
    int ennemy_type = rand() % 4;
    if (ennemy_type == 0) {
        r.add_component<drawable>(ennemy, {_spriteManager.Get("ennemy")});
        r.add_component<position>(ennemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 64))});
        r.add_component<velocity>(ennemy, {-3, 0});
        r.add_component<animation_adaptative>(ennemy, {sf::IntRect(0, 0, 64, 64), 0, 0, 0.5f});
        r.add_component<collidable>(ennemy, {});
        r.add_component<is_ally>(ennemy, {false});
        r.add_component<health>(ennemy, {20});
        r.add_component<attack>(ennemy, {10});
    } else if (ennemy_type == 1) {
        r.add_component<drawable>(ennemy, {_spriteManager.Get("ennemy_02")});
        r.add_component<position>(ennemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 32))});
        r.add_component<velocity>(ennemy, {-5, 0});
        r.add_component<animation_basic>(ennemy, {sf::IntRect(0, 0, 32, 32), 0, 2, 32, 0.2f});
        r.add_component<collidable>(ennemy, {});
        r.add_component<is_ally>(ennemy, {false});
        r.add_component<health>(ennemy, {1});
        r.add_component<attack>(ennemy, {10});
    } else if (ennemy_type == 2) {
        r.add_component<drawable>(ennemy, {_spriteManager.Get("ennemy_03")});
        r.add_component<position>(ennemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 96))});
        r.add_component<velocity>(ennemy, {-1, 0});
        r.add_component<animation_basic>(ennemy, {sf::IntRect(0, 0, 96, 96), 0, 4, 96, 0.3f});
        r.add_component<collidable>(ennemy, {});
        r.add_component<is_ally>(ennemy, {false});
        r.add_component<health>(ennemy, {40});
        r.add_component<attack>(ennemy, {10});
    } else if (ennemy_type == 3) {
        r.add_component<drawable>(ennemy, {_spriteManager.Get("boss")});
        r.add_component<position>(ennemy, {static_cast<float>(w.getSize().x) * 0.7f, static_cast<float>(100)});
        r.add_component<animation_basic>(ennemy, {sf::IntRect(0, 0, 100, 100), 0, 13, 100, 0.2f});
        r.add_component<collidable>(ennemy, {});
        r.add_component<resizable>(ennemy, {4, 4});
        r.add_component<is_ally>(ennemy, {false});
        r.add_component<health>(ennemy, {100});
        r.add_component<attack>(ennemy, {100});
        r.add_component<is_boss>(ennemy, {});
    }
    last_time = current_time;
}

void GameStd::bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager)
{
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::seconds time_span = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time);

    if (time_span < std::chrono::seconds(1))
        return;
    entity_t bullet = r.spawn_entity();
    r.add_component<drawable>(bullet, {_spriteManager.Get("bullet")});
    r.add_component<position>(bullet, {src_x + 64, src_y + 8});
    r.add_component<velocity>(bullet, {10, 0});
    r.add_component<animation_basic>(bullet, {sf::IntRect(0, 34, 50, 17), 0, 8, 50, 0.1f});
    r.add_component<collidable>(bullet, {});
    r.add_component<is_ally>(bullet, {true});
    r.add_component<attack>(bullet, {10});
    r.add_component<health>(bullet, {1});
    last_time = current_time;
}

void GameStd::boss_magic_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w)
{
    int bosses = 0;
    auto &are_bosses = r.get_components<is_boss>();
    for (size_t i = 0; i < are_bosses.size(); ++i) {
        if (are_bosses[i])
            bosses++;
    }
    if (!bosses)
        return;
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::seconds time_span = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time);
    if (time_span < std::chrono::seconds(1))
        return;
    entity_t magic = r.spawn_entity();
    r.add_component<drawable>(magic, {_spriteManager.Get("black_magic")});
    r.add_component<position>(magic, {static_cast<float>(w.getSize().x) * 0.9f, 400.0f});
    float random_x_vel = static_cast<float>(rand() % 100) / 10;
    float random_y_vel = (static_cast<float>(rand() % 100) - 50) / 10;
    r.add_component<velocity>(magic, {-1 * random_x_vel, random_y_vel});
    r.add_component<animation_basic>(magic, {sf::IntRect(0, 0, 70, 100), 0, 10, 70, 0.2f});
    r.add_component<is_ally>(magic, {false});
    r.add_component<collidable>(magic, {});
    r.add_component<attack>(magic, {10});
    r.add_component<health>(magic, {20});

    last_time = current_time;
}
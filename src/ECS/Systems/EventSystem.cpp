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

void GameStd::bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager)
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
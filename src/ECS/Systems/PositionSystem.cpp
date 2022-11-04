/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** PositionSystem
*/

#include "System.hpp"

bool GameStd::is_ship_out_system(std::optional<position> pos, std::optional<velocity> vel, Window_ref w)
{
    if (pos->x + vel->x < 0)
        return true;
    if (pos->x + vel->x > w.getSize().x - 48.0)
        return true;
    if (pos->y + vel->y < 0)
        return true;
    if (pos->y + vel->y > w.getSize().y - 32.0)
        return true;
    return false;
}

void GameStd::position_system(registry &r, Window_ref w, Client &client)
{
    auto &positions = r.get_components<struct position>();
    auto &controlables = r.get_components<struct controlable>();
    auto &velocities = r.get_components<struct velocity>();
    auto &are_ships = r.get_components<struct is_ship>();

    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        if (i < are_ships.size() && are_ships[i] && is_ship_out_system(positions[i], velocities[i], w)) {
            client.sendPos(positions[i]->x, positions[i]->y);
            continue;
        }
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

void GameStd::remove_out_of_screen_system(registry &r, Window_ref w)
{
    auto &positions = r.get_components<position>();
    auto &drawables = r.get_components<drawable>();
    auto &are_backgrounds = r.get_components<is_background>();

    for (size_t i = 0; i < positions.size() && i < drawables.size(); ++i)
    {
        if (positions[i] && drawables[i] && i < are_backgrounds.size() && !are_backgrounds[i]) {
            if (positions[i]->x > static_cast<float>(w.getSize().x) || positions[i]->x < 0 || positions[i]->y > static_cast<float>(w.getSize().y) || positions[i]->y < 0)
                r.kill_entity(r.entity_from_index(i));
        }
        if (positions[i] && drawables[i] && i < are_backgrounds.size() && are_backgrounds[i]) {
            if (positions[i]->x < -static_cast<float>(w.getSize().x))
                positions[i]->x = 0;
        }
    }
}

void GameStd::collision_system(registry &r, AudioManager<std::string>& _audioManager)
    {
        auto &collidables = r.get_components<struct collidable>();
        auto &drawables = r.get_components<struct drawable>();
        auto &are_allies = r.get_components<is_ally>();
        auto &attack = r.get_components<struct attack>();
        auto &healths = r.get_components<struct health>();
        auto &death_sfxs = r.get_components<struct death_sfx>();

        for (unsigned int idx_1 = 0; idx_1 < collidables.size() && idx_1 < drawables.size() && idx_1 < are_allies.size(); ++idx_1) {
            for (unsigned int idx_2 = idx_1 + 1; idx_2 < collidables.size() && idx_2 < drawables.size() && idx_2 < are_allies.size(); ++idx_2) {
                if (collidables[idx_1] && collidables[idx_2] &&
                    drawables[idx_1] && drawables[idx_2] &&
                    are_allies[idx_1]->status != are_allies[idx_2]->status) {
                    if (drawables[idx_1]->sprite.getGlobalBounds().intersects(drawables[idx_2]->sprite.getGlobalBounds())) {
                        if (idx_1 < attack.size() && idx_1 < healths.size() &&
                            idx_2 < attack.size() && idx_2 < healths.size() &&
                            attack[idx_1] && healths[idx_1] && attack[idx_2] && healths[idx_2]) {
                            healths[idx_2]->hp -= attack[idx_1]->damage;
                            healths[idx_1]->hp -= attack[idx_2]->damage;
                            if (healths[idx_2]->hp <= 0) {
                                if (idx_2 < death_sfxs.size() && death_sfxs[idx_2])
                                    _audioManager.play(death_sfxs[idx_2]->key);
                                r.kill_entity(r.entity_from_index(idx_2));
                            }
                            if (healths[idx_1]->hp <= 0) {
                                if (idx_1 < death_sfxs.size() && death_sfxs[idx_1])
                                    _audioManager.play(death_sfxs[idx_1]->key);
                                r.kill_entity(r.entity_from_index(idx_1));
                            }
                        }
                    }
                }
            }
        }
    }
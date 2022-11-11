/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EventSystem
*/

#include "System.hpp"
#include "Languages.hpp"
#include "Globals.hpp"

int count_bosses(Registry_ref reg)
{
    int count = 0;
    auto &boss_component_vec = reg.get_components<is_boss>();

    for (size_t i = 0; i < boss_component_vec.size(); ++i)
        if (boss_component_vec[i])
            count++;
    return count;
}

void User::enemy_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w)
{
    if (count_bosses(r) || Globals::difficulty == 0)
        return;
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::seconds time_span = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time);
    if (time_span < std::chrono::seconds(2))
        return;
    entity_t enemy = r.spawn_entity();
    int enemy_type = rand() % Globals::difficulty;
    if (enemy_type == 0) {
        r.add_component<drawable>(enemy, {_spriteManager.Get("enemy")});
        r.add_component<position>(enemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 64))});
        r.add_component<velocity>(enemy, {-3, 0});
        r.add_component<animation_adaptative>(enemy, {sf::IntRect(0, 0, 64, 64), 0, 0, 0.5f});
        r.add_component<collidable>(enemy, {});
        r.add_component<is_ally>(enemy, {false});
        r.add_component<health>(enemy, {20});
        r.add_component<attack>(enemy, {10});
        r.add_component<value_score>(enemy, {10});
    } else if (enemy_type == 1) {
        r.add_component<drawable>(enemy, {_spriteManager.Get("enemy_02")});
        r.add_component<position>(enemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 32))});
        r.add_component<velocity>(enemy, {-5, 0});
        r.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 32, 32), 0, 2, 32, 0.2f});
        r.add_component<collidable>(enemy, {});
        r.add_component<is_ally>(enemy, {false});
        r.add_component<health>(enemy, {1});
        r.add_component<attack>(enemy, {10});
        r.add_component<value_score>(enemy, {1});
    } else if (enemy_type == 2) {
        r.add_component<drawable>(enemy, {_spriteManager.Get("enemy_03")});
        r.add_component<position>(enemy, {static_cast<float>(w.getSize().x) * 0.9f, static_cast<float>(rand() % (w.getSize().y - 96))});
        r.add_component<velocity>(enemy, {-1, 0});
        r.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 96, 96), 0, 4, 96, 0.3f});
        r.add_component<collidable>(enemy, {});
        r.add_component<is_ally>(enemy, {false});
        r.add_component<health>(enemy, {40});
        r.add_component<attack>(enemy, {10});
        r.add_component<value_score>(enemy, {100});
    } else if (enemy_type == 3) {
        r.add_component<drawable>(enemy, {_spriteManager.Get("boss")});
        r.add_component<position>(enemy, {static_cast<float>(w.getSize().x) * 0.7f, static_cast<float>(100)});
        r.add_component<animation_basic>(enemy, {sf::IntRect(0, 0, 100, 100), 0, 13, 100, 0.2f});
        r.add_component<collidable>(enemy, {});
        r.add_component<resizable>(enemy, {4, 4});
        r.add_component<is_ally>(enemy, {false});
        r.add_component<health>(enemy, {100});
        r.add_component<attack>(enemy, {100});
        r.add_component<value_score>(enemy, {1000});
        r.add_component<is_boss>(enemy, {});
    }
    last_time = current_time;
}

void User::bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager, AudioManager<std::string>& _audioManager, Client &client)
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
    _audioManager.play("blaster");
    client.sendBlaster(src_x + 64, src_y + 8);
    last_time = current_time;
}

void User::boss_magic_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w)
{
    if (!count_bosses(r))
        return;
    static std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();
    std::chrono::seconds time_span = std::chrono::duration_cast<std::chrono::seconds>(current_time - last_time);
    if (time_span < std::chrono::seconds(1))
        return;
    entity_t magic = r.spawn_entity();
    float random_x_vel = static_cast<float>(rand() % 100) / 10;
    float random_y_vel = (static_cast<float>(rand() % 100) - 50) / 10;

    r.add_component<drawable>(magic, {_spriteManager.Get("black_magic")});
    r.add_component<position>(magic, {static_cast<float>(w.getSize().x) * 0.9f, 400.0f});
    r.add_component<velocity>(magic, {-1 * random_x_vel, random_y_vel});
    r.add_component<animation_basic>(magic, {sf::IntRect(0, 0, 70, 100), 0, 10, 70, 0.2f});
    r.add_component<is_ally>(magic, {false});
    r.add_component<collidable>(magic, {});
    r.add_component<attack>(magic, {10});
    r.add_component<health>(magic, {20});

    last_time = current_time;
}

bool User::check_lose_system(Registry_ref reg, SceneManager_ref<std::string> scene)
{
    int ally_count = 0;
    auto &is_ships = reg.get_components<is_ship>();

    for (size_t i = 0; i < is_ships.size(); ++i) {
        if (is_ships[i])
            ally_count++;
    }
    return !ally_count;
}

void User::update_score(registry &r)
{
    auto &texts = r.get_components<text>();
    auto &scores = r.get_components<is_score>();
    std::stringstream ss;
    ss << Globals::score;
    std::string str;
    ss >> str;

    for (size_t i = 0; i < scores.size() && i < texts.size(); ++i) {
        if (scores[i] && texts[i]) {
            texts[i]->text_str = std::string(dictionnary_language["score"] + std::string(": ") + str);
        }
    }
}
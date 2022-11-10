/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DisplaySystem
*/

#include "System.hpp"
#include "Globals.hpp"

/**
 * @brief display the hitboxes of the entities if the debug mode is activated
 *
 * @param w : the window reference
 * @param s :the sprite reference
 * @param team : the team if the entity has one (optional)
 */
static void display_debug_mode(sf::RenderWindow &w, sf::Sprite &s, std::optional<is_ally> team)
{
    sf::RectangleShape rect;

    rect.setPosition(s.getPosition());
    rect.setSize(sf::Vector2f(s.getGlobalBounds().width, s.getGlobalBounds().height));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    if (team && team->status == true)
        rect.setOutlineColor(sf::Color::Green);
    rect.setOutlineThickness(2);
    w.draw(rect);
}


void User::draw_system(registry &r, Window_ref w)
{
    auto &drawables = r.get_components<drawable>();
    auto &positions = r.get_components<position>();
    auto &animation_adaptatives = r.get_components<struct animation_adaptative>();
    auto &resizables = r.get_components<struct resizable>();
    auto &are_allies = r.get_components<is_ally>();
    auto &textables = r.get_components<text>();
    bool collision_box = Globals::debug_mode;

    animation_basic_system(r);
    for (size_t i = 0; i < drawables.size(); ++i) {
        if (drawables[i]) {
            if (i < positions.size() && positions[i])
                drawables[i]->sprite.setPosition(positions[i]->x, positions[i]->y);
            if (i < animation_adaptatives.size() && animation_adaptatives[i])
                drawables[i]->sprite.setTextureRect(animation_adaptatives[i]->rect);
            if (i < resizables.size() && resizables[i])
                drawables[i]->sprite.setScale(resizables[i]->x, resizables[i]->y);
            if (collision_box && i < are_allies.size()) {
                display_debug_mode(w, drawables[i]->sprite, are_allies[i]);
            }
            w.draw(drawables[i]->sprite);
        }
    }
    for (size_t i = 0; i < textables.size(); ++i) {
        if (textables[i]) {
            sf::Text text_object;
            text_object.setFont(Globals::font);
            text_object.setString(textables[i]->text);
            if (i < positions.size() && positions[i])
                text_object.setPosition(positions[i]->x, positions[i]->y);
            if (i < resizables.size() && resizables[i])
                text_object.setScale(resizables[i]->x, resizables[i]->y);
            w.draw(text_object);
        }
    }
}
/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** SceneSystem
*/

#include "../../sfml_ref.hpp"
#include "System.hpp"

// template<typename Key>
// void User::click_system(Registry_ref reg, SceneManager_ref<Key> scene, Event_ref event, Window_ref window)
// {
//     auto &clickables = reg.get_components<clickable>();
//     auto &drawables = reg.get_components<drawable>();
//     auto &positions = reg.get_components<position>();

//     if (event.type == sf::Event::MouseButtonPressed) {
//         for (size_t i = 0; i < drawables.size() && i < positions.size() && i < clickables.size(); ++i) {
//             if (drawables[i] && positions[i] && clickables[i]) {
//                 if (drawables[i]->sprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) {
//                     std::cout << "CLICK ON SPRITE" << std::endl;
//                     clickables[i]->callback(scene);
//                 }
//             }
//         }
//     }
// }
/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ClickActions
*/

#ifndef CLICKACTIONS_HPP_
#define CLICKACTIONS_HPP_

#include "../../../SceneManager/SceneManager.hpp"

void back_to_game(SceneManager_ref<std::string> scene);

void exit_game(SceneManager_ref<std::string> scene);

void pop_settings(SceneManager_ref<std::string> scene);

void switch_language_to_fr(SceneManager_ref<std::string> scene);

void switch_language_to_eng(SceneManager_ref<std::string> scene);

void switch_language_to_jap(SceneManager_ref<std::string> scene);

void switch_language_to_spa(SceneManager_ref<std::string> scene);

#endif /* !CLICKACTIONS_HPP_ */

/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ClickActions
*/

#ifndef CLICKACTIONS_HPP_
#define CLICKACTIONS_HPP_

#include "AudioManager.hpp"
#include "MusicManager.hpp"
#include "../../../SceneManager/SceneManager.hpp"


void back_to_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void exit_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void pop_settings(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void upgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void downgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void upgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void downgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void switch_language_to_fr(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void switch_language_to_eng(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void switch_language_to_jap(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

void switch_language_to_spa(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

#endif /* !CLICKACTIONS_HPP_ */

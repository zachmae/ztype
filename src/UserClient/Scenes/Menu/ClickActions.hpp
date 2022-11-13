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

/**
 * @brief switch the current scene to the game scene
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void back_to_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief leave the game
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void exit_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief switch the current scene to the settings scene
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void pop_settings(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief raise volume of the audio manager by 10
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void upgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief lower volume of the audio manager by 10
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void downgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief raise volume of the music manager by 10
 *
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void upgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief lower volume of the music manager by 10
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void downgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief switch language to french
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void switch_language_to_fr(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief switch language to english
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void switch_language_to_eng(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief switch language to japanese
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void switch_language_to_jap(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

/**
 * @brief switch language to spanish
 * 
 * @param scene reference to the scene manager
 * @param am reference to the audio manager
 * @param mm reference to the music manager
 */
void switch_language_to_spa(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);

#endif /* !CLICKACTIONS_HPP_ */

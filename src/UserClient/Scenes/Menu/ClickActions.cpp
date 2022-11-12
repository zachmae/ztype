/*
** EPITECH PROJECT, 2022
** B-CPP-500-PAR-5-1-rtype-zacharie.lawson
** File description:
** ClickActions
*/

#include "Languages.hpp"
#include "ClickActions.hpp"

void back_to_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    // SceneManager_ref<std::string> scene(p...);

    scene.Get("menu").SetZIndex(-1);
    // std::cout << "                          TEST" << std::endl;
}

void exit_game(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    scene.Get("menu").SetZIndex(-1);
    scene.Get("game").SetZIndex(-1);
}

void pop_settings(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    if (scene.Get("menu").GetZIndex() == 2)
        scene.Get("game").SetZIndex(-1);
    scene.Get("menu").SetZIndex(2);
}

void upgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    float vol = am.getVolume();
    std::cout << "Volume am up: " << vol << std::endl;
    if (vol < 100.0f)
        am.setVolume(vol + 10);
}

void downgrade_audio(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    float vol = am.getVolume();
    std::cout << "Volume am down: " << vol << std::endl;
    if (vol > 0.0f)
        am.setVolume(vol - 10);
}

void upgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    float vol = mm.getVolume();
    std::cout << "Volume mm up: " << vol << std::endl;
    if (vol < 100.0f)
        mm.setVolume(vol + 10);
}

void downgrade_music(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    float vol = mm.getVolume();
    std::cout << "Volume mm down: " << vol << std::endl;
    if (vol > 0.0f)
        mm.setVolume(vol - 10);
}

void switch_language_to_fr(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    load_language(std::string("fr"));
}

void switch_language_to_eng(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    load_language(std::string("en"));
}

void switch_language_to_jap(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    load_language(std::string("jp"));
}

void switch_language_to_spa(SceneManager_ref<std::string> scene, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm)
{
    load_language(std::string("es"));
}
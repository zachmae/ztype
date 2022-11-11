/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** System
*/

#include <optional>
#include <chrono>
#include "../../ProjectManager/Ecs.hpp"
#include "../ClientComponent.hpp"
#include "../../SpriteManager.hpp"
#include "SceneManager/SceneManager.hpp"
#include "../../AudioManager.hpp"
#include "../../Network/Client.hpp"
#include "../../Network/Server.hpp"

#include "../../sfml_ref.hpp"

/*!
 *  \addtogroup System
 *  @{
 */

//! Namespace for all game related content, here systems
namespace User {


    /**
     * @brief System that replace the ship if he goes out of screen
     *
     * @param pos : position of the ship
     * @param vel : velocity of the ship (position after the next move)
     * @param w : window reference
     * @return true : if the ship is out of screen
     * @return false : if the ship is not out of screen
     */
    bool is_ship_out_system(std::optional<position> pos, std::optional<velocity> vel, Window_ref w);

    /**
     * @brief : handle position of all of the entities
     *
     * @param r : registry, contain all of the entities and the related components
     * @param w : window reference
     * @param client : client reference
     */
    void position_system(registry &r, Window_ref w, Client &client);

    /**
     * @brief handle basic animations in a sprite sheet
     *
     * @param r : registry, contain all of the entities and the related components
     */
    void animation_basic_system(registry &r);

    /**
     * @brief update the score object
     *
     * @param r : registry, contain all of the entities and the related components
     */
    void update_score(registry &r);

    /**
     * @brief update button text language
     *
     * @param r : registry, contain all of the entities and the related components
     */
    void update_button_language(registry &r);

    /**
     * @brief update music text volume
     *
     * @param r : registry, contain all of the entities and the related components
     * @param mm : the reference to the music manager
     */
    void update_music_volume_text(registry &r, MusicManager_ref<std::string> mm);

    /**
     * @brief update music text volume
     *
     * @param r : registry, contain all of the entities and the related components
     * @param mm : the reference to the music manager
     */
    void update_audio_volume_text(registry &r, AudioManager_ref<std::string> am);

    /**
     * @brief system that can animate ships
     *
     * @param r : registry, contain all of the entities and the related components
     * @param entity_index : index of the entity i want to animate
     * @param key_code : key code of the key pressed
     */
    void animate_ship_system(registry &r, size_t entity_index, int key_code);

    /**
     * @brief system that can create a bullet from the position of the ship
     *
     * @param r : registry, contain all of the entities and the related components
     * @param src_x : x position of the ship
     * @param src_y : y position of the ship
     * @param _spriteManager : sprite manager reference of all sprites
     */
    void bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager, AudioManager<std::string>& _audioManager, SceneManager_ref<std::string> scene);

    /**
     * @brief system that can create random enemy when i need to
     *
     * @param r : registry, contain all of the entities and the related components
     * @param _spriteManager : sprite manager reference of all sprites
     * @param w : window reference
     */
    void enemy_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w, SceneManager_ref<std::string> scene);

    /**
     * @brief system that allow the generation of magic attack if the boss is alive
     *
     * @param r : registry, contain all of the entities and the related components
     * @param _spriteManager : sprite manager reference of all sprites
     * @param w : window reference
     */
    void boss_magic_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w, SceneManager_ref<std::string> scene);

    /**
     * @brief system that check if there is player left alive
     *
     * @param reg : registry, contain all of the entities and the related components
     * @param scene : scene manager reference
     * @return true : if there is no player left alive
     * @return false : if there is still player left alive
     */
    bool check_lose_system(Registry_ref reg, SceneManager_ref<std::string> scene);

    /**
     * @brief system that handle collision between entities
     *
     * @param r : registry, contain all of the entities and the related components
     * @param _audioManager : audio manager reference of all sounds
     */
    void collision_system(registry &r, AudioManager<std::string>& _audioManager);

    /**
     * @brief system that can handle controls of the entities that i am able to move
     *
     * @param r : registry, contain all of the entities and the related components
     * @param e : event that i want to handle
     * @param _spriteManager : sprite manager reference of all sprites
     */
    void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager, AudioManager<std::string>& _audioManager, SceneManager_ref<std::string> scene);

    /**
     * @brief system that can remove every entities that are out of the window in order to free memory
     *
     * @param r : registry, contain all of the entities and the related components
     * @param w : window reference
     */
    void remove_out_of_screen_system(registry &r, Window_ref w);

    /**
     * @brief system that draw every drawable entity
     *
     * @param r : registry, contain all of the entities and the related components
     * @param w : window reference
     */
    void draw_system(registry &r, Window_ref w);

    /**
     * @brief click system
     *
     * @param reg : the reference to the registry
     * @param scene : the reference to the scene manager
     * @param event
     * @param window
     * @param am : the reference to the audio manager
     * @param mm : the reference to the music manager
     */
    template<typename Key>
    void click_system(Registry_ref reg, SceneManager_ref<Key> scene, Event_ref event, Window_ref window, AudioManager_ref<std::string> am, MusicManager_ref<std::string> mm);
}
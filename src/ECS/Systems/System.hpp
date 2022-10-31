/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** System
*/

#include <optional>
#include <chrono>
#include "Ecs.hpp"
#include "Component.hpp"
#include "SpriteManager.hpp"
#include "AudioManager.hpp"
#include "../../Network/Client.hpp"
#include "../../Network/Server.hpp"

/*!
 *  \addtogroup System
 *  @{
 */

//! Namespace for all game related content, here systems
namespace GameStd {

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
     * @brief : handle position of all of the entities but is deprecated
     *
     * @param r : registry, contain all of the entities and the related components
     * @param w : window reference
     * @param server : server reference
     */
    [[deprecated]] inline void position_system(registry &r, Window_ref w, Server &server)
    {
        auto &positions = r.get_components<struct position>();
        auto &controlables = r.get_components<struct controlable>();
        auto &velocities = r.get_components<struct velocity>();
        auto &are_ships = r.get_components<struct is_ship>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            if (i < are_ships.size() && are_ships[i] && is_ship_out_system(positions[i], velocities[i], w)) {
                server.sendPos(positions[i]->x, positions[i]->y);
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

    /**
     * @brief handle basic animations in a sprite sheet
     *
     * @param r : registry, contain all of the entities and the related components
     */
    void animation_basic_system(registry &r);

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
    void bullet_creation_system(registry &r, float src_x, float src_y, SpriteManager<std::string> _spriteManager, AudioManager<std::string>& _audioManager);

    /**
     * @brief system that can create random ennemy when i need to
     *
     * @param r : registry, contain all of the entities and the related components
     * @param _spriteManager : sprite manager reference of all sprites
     * @param w : window reference
     */
    void ennemy_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w);

    /**
     * @brief system that allow the generation of magic attack if the boss is alive
     *
     * @param r : registry, contain all of the entities and the related components
     * @param _spriteManager : sprite manager reference of all sprites
     * @param w : window reference
     */
    void boss_magic_system(registry &r, SpriteManager<std::string>& _spriteManager, Window_ref w);


    /**
     * @brief system that handle collision between entities
     *
     * @param r : registry, contain all of the entities and the related components
     */
    void collision_system(registry &r);

    /**
     * @brief system that can handle controls of the entities that i am able to move
     *
     * @param r : registry, contain all of the entities and the related components
     * @param e : event that i want to handle
     * @param _spriteManager : sprite manager reference of all sprites
     */
    void control_system(registry &r, Event_ref e, const SpriteManager<std::string>& _spriteManager, AudioManager<std::string>& _audioManager);

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
}
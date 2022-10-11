/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** game
*/

#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "System.hpp"
#include "SpriteManager.hpp"
#include <map>

//#include "System.hpp"

namespace GameStd {

    /**
     * @brief GameManager
     *
     */
    class GameManager {
        public:
            using Window_ref = sf::RenderWindow &;
            using Event_ref = sf::Event &;
            using Music_ref = sf::Music &;
            using Sound_ref = sf::Sound &;

            /**
             * @brief GameManager copy constructor deleted
             *
             */
            GameManager(GameManager &) = delete;

            /**
             * @brief GameManager move constructor deleted
             *
             */
            GameManager(GameManager const &&) = delete;
            ~GameManager() = default;

            /**
             * @brief Construct a new Game Manager object
             *
             * @param window
             * @param event
             */

            GameManager(Window_ref window, Event_ref event)
            : _window(window), _event(event)
            {
                _spriteManager.Add("spaceship", "assets/___fav___r-typesheet21.gif");
                _ecs.register_component<drawable>();
                _ecs.register_component<position>();
                _ecs.register_component<velocity>();
                _ecs.register_component<contralable>();
                entity_t e = _ecs.spawn_entity();
                _ecs.add_component<drawable>(e, {sprite:_spriteManager.Get("spaceship")});
                _ecs.add_component<position>(e, {.x = 0, .y = 0});
                _ecs.add_component<velocity>(e, {.x = 0, .y = 0});
                _ecs.add_component<contralable>(e, {});
            };

            //! not working
            /**
             * @brief
             *
             * @param sf::Vector2f &
             * @return position
             */
/*            GameStd::position operator=(sf::Vector2f &pos)
            {
                return std::pair<float, float>({pos.x, pos.y});
            }*/

            int run()
            {
//                _ecs.add_component<>
                    // run the program as long as the window is open

                while (_window.isOpen()) {
                    _window.clear();
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _window.close();
                            return 0;
                        }
                        control_system(_ecs, _event);
                    }
                    position_system(_ecs);
                    draw_system(_ecs, _window);
                    _window.display();
                }
                return 0;
            };

        private:
            Window_ref _window;
            Event_ref _event;
            registry _ecs;
            SpriteManager<std::string> _spriteManager;
    };
};

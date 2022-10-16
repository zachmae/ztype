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
                _window.setFramerateLimit(60);

                _ecs.register_component<drawable>();
                _ecs.register_component<position>();
                _ecs.register_component<velocity>();
                _ecs.register_component<controlable>();
                _ecs.register_component<animation_adaptative>();
                _ecs.register_component<animation_basic>();
                _ecs.register_component<resizable>();
                _ecs.register_component<is_ship>();
                _ecs.register_component<collidable>();
                _ecs.register_component<is_background>();

                entity_t background = _ecs.spawn_entity();
                _spriteManager.Add("background_back", "../assets/img/background/parallax_back.png");
                _ecs.add_component<drawable>(background, {_spriteManager.Get("background_back")});
                _ecs.add_component<position>(background, {0, 0});
                _ecs.add_component<velocity>(background, {-0.1f, 0});
                _ecs.add_component<is_background>(background, {});

                entity_t background_stars = _ecs.spawn_entity();
                _spriteManager.Add("background_stars", "../assets/img/background/parallax_stars.png");
                _ecs.add_component<drawable>(background_stars, {_spriteManager.Get("background_stars")});
                _ecs.add_component<position>(background_stars, {0, 0});
                _ecs.add_component<velocity>(background_stars, {-0.2f, 0});
                _ecs.add_component<is_background>(background_stars, {});

                entity_t background_planets_back = _ecs.spawn_entity();
                _spriteManager.Add("background_planets_back", "../assets/img/background/parallax_planets_back.png");
                _ecs.add_component<drawable>(background_planets_back, {_spriteManager.Get("background_planets_back")});
                _ecs.add_component<position>(background_planets_back, {0, 0});
                _ecs.add_component<velocity>(background_planets_back, {-0.5f, 0});
                _ecs.add_component<is_background>(background_planets_back, {});

                entity_t background_planets_front = _ecs.spawn_entity();
                _spriteManager.Add("background_planets_front", "../assets/img/background/parallax_planets_front.png");
                _ecs.add_component<drawable>(background_planets_front, {_spriteManager.Get("background_planets_front")});
                _ecs.add_component<position>(background_planets_front, {0, 0});
                _ecs.add_component<velocity>(background_planets_front, {-0.8f, 0});
                _ecs.add_component<is_background>(background_planets_front, {});

                entity_t ship = _ecs.spawn_entity();
                _spriteManager.Add("ship", "../assets/img/spaceship.gif");
                _ecs.add_component<drawable>(ship, {_spriteManager.Get("ship")});
                _ecs.add_component<position>(ship, {100, 300});
                _ecs.add_component<velocity>(ship, {2, 2});
                _ecs.add_component<controlable>(ship, {});
                _ecs.add_component<animation_adaptative>(ship, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                _ecs.add_component<resizable>(ship, {2, 2});
                _ecs.add_component<is_ship>(ship, {});
                _ecs.add_component<collidable>(ship, {});

                _spriteManager.Add("bullet", "../assets/img/fx_02.gif");
                _spriteManager.Add("ennemy", "../assets/img/enemy_01.gif");
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
                        control_system(_ecs, _event, _spriteManager);
                    }
                    ennemy_system(_ecs, _spriteManager, _window);
                    position_system(_ecs, _window);
                    draw_system(_ecs, _window);
                    _window.display();
                    collision_system(_ecs);
                    remove_out_of_screen_system(_ecs, _window);
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

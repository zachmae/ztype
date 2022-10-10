/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** game
*/

#ifndef _GAME_HPP_
    #define _GAME_HPP_
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "Ecs.hpp"
#include <map>
//#include "System.hpp"



namespace GameStd {
    // ~
    using Window_ref = sf::RenderWindow &;
    using Event_ref = sf::Event &;

    struct position {
        float x;
        float y;
    };
    
    struct velocity {
        float x;
        float y;
    };

    struct drawable {
        sf::Sprite sprite;
    };

    struct contralable {
    };
    
    struct Image {
        sf::Texture texture;
        sf::Sprite sprite;
    };

    inline void position_system(registry &r)
    {
        auto &positions = r.get_components<struct position>();
        auto &velocities = r.get_components<struct velocity>();

        for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
            if (positions[i] && velocities[i]) {
                positions[i]->x += velocities[i]->x;
                positions[i]->y += velocities[i]->y;
            }
        }
        for (size_t i = 0; i < velocities.size(); ++i) {
            if (velocities[i]) {
                velocities[i]->y = 0;
                velocities[i]->x = 0;
            }
        }
    }

    inline void control_system(registry &r, Event_ref e)
    {
        auto &controllables = r.get_components<contralable>();
        auto &velocities = r.get_components<velocity>();
        for (size_t i = 0; i < controllables.size() && i < velocities.size(); ++i) {
            if (velocities[i] && controllables[i] && e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Z) {
                    velocities[i]->y = -10;
                } if (e.key.code == sf::Keyboard::S) {
                    velocities[i]->y = 10;
                } if (e.key.code == sf::Keyboard::Q) {
                    velocities[i]->x = -10;
                } if (e.key.code == sf::Keyboard::D) {
                    velocities[i]->x = 10;
                }
            }
        }
    }

    inline void draw_system(registry &r, Window_ref w)
    {
        auto &drawables = r.get_components<drawable>();
        auto &positions = r.get_components<position>();

        w.clear(sf::Color::Black);
        for (size_t i = 0; i < drawables.size() && i < positions.size(); ++i) {
            if (drawables[i] && positions[i]) {
                drawables[i]->sprite.setPosition({positions[i]->x, positions[i]->y});
                w.draw(drawables[i]->sprite);
            }
        }
        w.display();
    }

    /**
     * @brief StorageManager
     * 
     * @tparam T
     * @tparam Value
     */
    template<typename Key/*, typename Value*/>
    class StorageManager {
        public:
            using TStorage = std::map<Key, Image>;

            /**
             * @brief Add
             * 
             * @param t 
             * @param v 
             */
            void Add(Key k, Image &v)
            {
                _storage.insert(std::pair<Key, Image>(k, v));
            };

            /**
             * @brief Add
             * 
             * @param t
             * @param texture
             * @param f
             */
            void Add(Key k, std::string path)
            {
                _storage[k].texture.loadFromFile(path);
                _storage[k].sprite.setTexture(_storage[k].texture);
            };

            /**
             * @brief Get
             * 
             * @param t 
             * @return sf::Sprite 
             */
            sf::Sprite &Get(Key k)
            {
                return _storage[k].sprite;
            };

        private:
            TStorage _storage;
    };

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
                _storageManager.Add("spaceship", "assets/___fav___r-typesheet21.gif");
                _ecs.register_component<drawable>();
                _ecs.register_component<position>();
                _ecs.register_component<velocity>();
                _ecs.register_component<contralable>();
                entity_t e = _ecs.spawn_entity();
                _ecs.add_component<drawable>(e, {sprite:_storageManager.Get("spaceship")});
                _ecs.add_component<position>(e, {x:0, y:0});
                _ecs.add_component<velocity>(e, {x:0, y:0});
                _ecs.add_component<contralable>(e, {});

//                _ecs.add_component<position>(e, {0, 0});
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
            StorageManager<std::string> _storageManager;
/*            std::function<Image &(std::string)>_imageLoader = [] (std::string texture) {
                Image image;
                image.texture.loadFromFile(texture);
                image.sprite.setTexture(image.texture);
                return image;
            };*/

    };

};

#endif /* _GAME_HPP_ */
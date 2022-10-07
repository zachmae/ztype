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
#include "ecs.hpp"
#include <map>


namespace GameStd {
    // ~
    using position = std::pair<float, float>;
    using speed = float;
    using size = std::pair<float, float>;
    using direction = char;
//    using clickable = bool;
    using life = float;

    struct Image {
        sf::Texture texture;
        sf::Sprite sprite;
    };


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
             * @return Value 
             */
            Image &Get(Key k)
            {
                return _storage[k];
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
            using Audio_ref = sf::Window &;

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
                _storageManager.Add("pacman", "../assets/___fav___r-typesheet21.gif");
                _ecs.register_component<position>();
                _ecs.register_component<speed>();
                _ecs.register_component<size>();
                _ecs.register_component<direction>();
                entity_t e = _ecs.spawn_entity();
                _ecs.add_component<position>(e, std::make_pair(100, 100));
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
                Image img = _storageManager.Get("pacman");
                Image img2 = _storageManager.Get("pacman");
                while (_window.isOpen()) {
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            _window.close();
                            return 0;
                        }
                        if (_event.type == sf::Event::KeyPressed) {
                            if (_event.key.code == sf::Keyboard::Z) {
                                img.sprite.move(0, -10);
                            }
                            if (_event.key.code == sf::Keyboard::S) {
                                img.sprite.move(0, 10);
                            }
                            if (_event.key.code == sf::Keyboard::Q) {
                                img.sprite.move(-10, 0);
                            }
                            if (_event.key.code == sf::Keyboard::D) {
                                img.sprite.move(10, 0);
                            }
                        }
                    }

                    _window.clear();
                    _window.draw(img.sprite);
                    _window.draw(img2.sprite);
                    _window.display();
                }
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

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

namespace GameStd
{
    // ~
    using position = std::pair<float, float>;
    using speed = float;
    using size = std::pair<float, float>;
    using direction = char;
    //    using clickable = bool;
    using life = float;

    struct Image
    {
        sf::Texture texture;
        sf::Sprite sprite;
    };

    /**
     * @brief StorageManager
     *
     * @tparam T
     * @tparam Value
     */
    template <typename Key /*, typename Value*/>
    class StorageManager
    {
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
    class GameManager
    {
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
            _storageManager.Add("ship", "../assets/img/spaceship.gif");
            _storageManager.Add("background", "../assets/img/space_background.jpeg");
            _storageManager.Add("bullet", "../assets/img/fx_02.gif");
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
            _window.setFramerateLimit(60);
            Image img = _storageManager.Get("background");
            Image img2 = _storageManager.Get("ship");
            int x = 166 * 0.4;
            int bullet_anim = 0;
            sf::IntRect bullet_rect(0, 34, 50, 17);
            sf::IntRect rectsprite(x, 0, 32, 17);
            std::vector<Image> bullets;

            img2.sprite.setPosition(100, 100);
            img2.sprite.setScale(2, 2);
            while (_window.isOpen())
            {
                // check all the window's events that were triggered since the last iteration of the loop
                while (_window.pollEvent(_event))
                {
                    // "close requested" event: we close the window
                    if (_event.type == sf::Event::Closed)
                    {
                        _window.close();
                        return 0;
                    }
                    if (_event.type == sf::Event::KeyPressed)
                    {
                        if (_event.key.code == sf::Keyboard::Z)
                        {
                            img2.sprite.move(0, -2);
                            x += 166 * 0.2;
                            if (x > 166 * 0.8)
                                x = 166 * 0.8;
                        }
                        if (_event.key.code == sf::Keyboard::S)
                        {
                            img2.sprite.move(0, 2);
                            x -= 166 * 0.2;
                            if (x < 0)
                                x = 0;
                        }
                        if (_event.key.code == sf::Keyboard::Q)
                        {
                            img2.sprite.move(-2, 0);
                            x = 166 * 0.4;
                        }
                        if (_event.key.code == sf::Keyboard::D)
                        {
                            img2.sprite.move(2, 0);
                            x = 166 * 0.4;
                        }
                        if (_event.key.code == sf::Keyboard::Space)
                        {
                            Image bullet = _storageManager.Get("bullet");
                            //bullet.sprite.setScale(0.2, 0.2);
                            bullet.sprite.setPosition(img2.sprite.getPosition().x + 32, img2.sprite.getPosition().y + 8);
                            bullets.push_back(bullet);
                        }
                    }
                }
                rectsprite.left = x;
                img2.sprite.setTextureRect(rectsprite);
                _window.clear();
                _window.draw(img.sprite);
                _window.draw(img2.sprite);
                bullet_anim = (bullet_anim + 50) % 400;
                bullet_rect.left = bullet_anim;
                for (long unsigned int i = 0; i < bullets.size(); ++i) {
                    if (bullets[i].sprite.getPosition().x > 800) {
                        bullets.erase(bullets.begin() + i);
                        continue;
                    }
                    bullets[i].sprite.setTextureRect(bullet_rect);
                    bullets[i].sprite.move(2, 0);
                    _window.draw(bullets[i].sprite);
                }
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

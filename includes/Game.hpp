/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** game
*/

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "SpriteManager.hpp"
#include "AudioManager.hpp"
#include "MusicManager.hpp"
#include "../src/ECS/Systems/System.hpp"
#include "../src/Network/Client.hpp"
#include "../src/Network/Server.hpp"
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
                _ecs.register_component<int>();
                _ecs.register_component<is_background>();
                _ecs.register_component<is_ally>();
                _ecs.register_component<attack>();
                _ecs.register_component<health>();
                _ecs.register_component<is_boss>();
                _ecs.register_component<death_sfx>();

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

                ship = _ecs.spawn_entity();
                _audioManager.Add("explosion", "../assets/sounds/explosion.ogg");
                _spriteManager.Add("ship", "../assets/img/spaceship.gif");
                _ecs.add_component<drawable>(ship, {_spriteManager.Get("ship")});
                _ecs.add_component<position>(ship, {100, 300});
                _ecs.add_component<velocity>(ship, {2, 2});
//                _ecs.add_component<controlable>(ship, {});
                _ecs.add_component<animation_adaptative>(ship, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                _ecs.add_component<resizable>(ship, {2, 2});
                _ecs.add_component<is_ship>(ship, {});
                _ecs.add_component<collidable>(ship, {});
                _ecs.add_component<health>(ship, {1});
                _ecs.add_component<attack>(ship, {0});
                _ecs.add_component<death_sfx>(ship, {"explosion"});

                _spriteManager.Add("bullet", "../assets/img/fx_02.gif");
                _spriteManager.Add("ennemy", "../assets/img/enemy_01.gif");
                _spriteManager.Add("ennemy_02", "../assets/img/enemy_02.png");
                _spriteManager.Add("ennemy_03", "../assets/img/enemy_03.png");
                _spriteManager.Add("boss", "../assets/img/boss.png");
                _spriteManager.Add("black_magic", "../assets/img/black_magic.png");
                _audioManager.Add("blaster", "../assets/sounds/blaster.ogg");
                _musicManager.Add("epitomize", "../assets/sounds/epitomize.mp3");
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

            /**
             * @brief Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int run_client(std::string const &ip, unsigned short port)
            {
//                _ecs.add_component<>
                Client client(ip, port);
                _ecs.add_component<int>(ship, client.GetId()); // GET THE ID OF THE SHIP new client id
                _ecs.add_component<controlable>(ship, {});
                _ecs.add_component<is_ally>(ship, {true});
                _musicManager.play("epitomize");
                while (_window.isOpen()) { // run the program as long as the window is open
                    _window.clear();
                    // check all the window's events that were triggered since the last iteration of the loop
                    while (_window.pollEvent(_event)) {
                        // "close requested" event: we close the window
                        if (_event.type == sf::Event::Closed) {
                            client.disconnect();
                            _window.close();
                            return 0;
                        }
                        control_system(_ecs, _event, _spriteManager, _audioManager);
                    }
                    sf::Packet sfp = client.WaitReceive();
                    if (sfp.getData() != NULL) { //cond doesn't work
                        std::string comparator;
                        sfp >> comparator;
                        if (comparator == "new_client") {
                            /**
                            * @brief OLD CLIENT GET NEW SHIP
                            *
                            *
                            *
                            */
                            int newCliId = 0;
                            sfp >> newCliId;
                            // comment on stock les id des autres
                            entity_t newCliEntity = _ecs.spawn_entity();
                            _ecs.add_component<drawable>(newCliEntity, {_spriteManager.Get("ship")});
                            _ecs.add_component<position>(newCliEntity, {100, 400});
                            _ecs.add_component<velocity>(newCliEntity, {2, 2});
                            _ecs.add_component<controlable>(newCliEntity, {});
                            _ecs.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                            _ecs.add_component<resizable>(newCliEntity, {2, 2});
                            _ecs.add_component<is_ship>(newCliEntity, {});
                            _ecs.add_component<collidable>(newCliEntity, {});
                            _ecs.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                            _ecs.add_component<is_ally>(newCliEntity, {true});

                        } else if (comparator == "old_client") {
                            /**
                            * @brief NEW CLIENT GET OLD SHIP
                            *
                            *
                            *
                            */

                            int amount = 0;
                            int newCliId = 0;
                            sfp >> amount;
                            for (sfp >> newCliId; amount != 0; sfp >> newCliId, amount--) {
                                if (client.GetId() != newCliId) {
                                    entity_t newCliEntity = _ecs.spawn_entity();
                                    _ecs.add_component<drawable>(newCliEntity, {_spriteManager.Get("ship")});
                                    _ecs.add_component<position>(newCliEntity, {100, 200});
                                    _ecs.add_component<velocity>(newCliEntity, {2, 2});
                                    _ecs.add_component<controlable>(newCliEntity, {});
                                    _ecs.add_component<animation_adaptative>(newCliEntity, {sf::IntRect(static_cast<int>(166.0 * 0.4), 0, 32, 17), 0, 0, 0.1f});
                                    _ecs.add_component<resizable>(newCliEntity, {2, 2});
                                    _ecs.add_component<is_ship>(newCliEntity, {});
                                    _ecs.add_component<collidable>(newCliEntity, {});
                                    _ecs.add_component<int>(newCliEntity, static_cast<int>(newCliId));
                                }
                            }
                        } else if (comparator == "client_pos") {
                            /**
                             * @brief GET SHIP POSITION
                             *
                             *
                             *
                             */
                            int id = 0;
                            float x = 0;
                            float y = 0;
                            sfp >> id >> x >> y;
                            auto &controlables = _ecs.get_components<controlable>();
                            auto &positions = _ecs.get_components<position>();
                            int i = 0;
                            for(auto &control : controlables) {
                                if (control != std::nullopt && control.value().id == id) {
                                    if (positions[i] != std::nullopt)
                                        _ecs.add_component<position>(_ecs.entity_from_index(i), {x, y});
                                }
                                ++i;
                            }
                        } else {
                            std::cout << "unknow type" << std::endl;
                        }
                    }
                    /**
                     * @brief SEND SHIP POSITION
                     *
                     *
                     *
                     */
                    sf::Packet packet;
                    auto &positions = _ecs.get_components<position>();

                    if (positions[4] != std::nullopt) {
                        packet << "pos_client" << client.GetId() << positions[4].value().x << positions[4].value().y;
                        if (client.getSocket().send(packet) != sf::Socket::Status::Done) {
                            std::cerr << "Error : Sending failed (maybe server down)" << std::endl;
                            exit(84);
                        }
                    }
                    ennemy_system(_ecs, _spriteManager, _window);
                    boss_magic_system(_ecs, _spriteManager, _window);
                    position_system(_ecs, _window, client);
                    draw_system(_ecs, _window);
                    _window.display();
                    collision_system(_ecs, _audioManager);
                    remove_out_of_screen_system(_ecs, _window);
                }
                return 0;
            };

        /**
         * @brief Server
         *
         * @param ip
         * @param port
         * @return int
         */
        int run_server(unsigned short port)
        {
//                _ecs.add_component<>
            Server server(port);
            sf::TcpSocket *socket;
            sf::Packet sfp;
            std::string compare;

            while (_window.isOpen()) { // run the program as long as the window is open
                _window.clear();
                if (server.selectorWait()) {
                    if (server.isNewConnection()) {
                        std::cout << "New Client" << std::endl;
                        server.accept();
                    }
                    socket = server.isNewMessage();
                    if (socket != nullptr) {
                        sfp = server.receive(socket);

                        if (sfp.getData() != NULL) {
                            sfp >> compare;
                            if (compare == "pos_client") {
                                int id = 0;
                                float x = 0;
                                float y = 0;

                                sfp >> id >> x >> y;
                                int i = 0;
                                for (auto &client : server.getClients()) {
                                    if (i != id) {
                                        sf::Packet newSfp;

                                        newSfp << "client_pos" << id << x << y;
                                        client->send(newSfp);
                                    }
                                    ++i;
                                }
                            }
                        }
                    }
                }
                // check all the window's events that were triggered since the last iteration of the loop
                while (_window.pollEvent(_event)) {
                    // "close requested" event: we close the window
                    if (_event.type == sf::Event::Closed) {
                        _window.close();
                        return 0;
                    }
                }
            }
            return 0;
        };

        private:
            Window_ref _window;
            Event_ref _event;
            registry _ecs;
            SpriteManager<std::string> _spriteManager;
            AudioManager<std::string> _audioManager;
            MusicManager<std::string> _musicManager;

            entity_t ship = _ecs.entity_from_index(0);
    };
};

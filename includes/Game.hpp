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
#include "System.hpp"
#include "SpriteManager.hpp"
#include "Client.hpp"
#include "Server.hpp"
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

                entity_t background = _ecs.spawn_entity();
                _spriteManager.Add("background_space", "../assets/img/space_background.jpeg");
                _ecs.add_component<drawable>(background, {_spriteManager.Get("background_space")});
                _ecs.add_component<position>(background, {0, 0});

                entity_t ship = _ecs.spawn_entity();
                _spriteManager.Add("ship", "../assets/img/spaceship.gif");
                _ecs.add_component<drawable>(ship, {_spriteManager.Get("ship")});
                _ecs.add_component<position>(ship, {100, 300});
                _ecs.add_component<velocity>(ship, {2, 2});
//                _ecs.add_component<controlable>(ship, {});
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

            /**
             * @brief Client
             *
             * @param ip
             * @param port
             * @return int
             */
            int run(std::string const &ip, unsigned short port)
            {
//                _ecs.add_component<>
                Client client(ip, port);
                _ecs.add_component<int>(_ecs.entity_from_index(1), client.GetId()); // GET THE ID OF THE SHIP new client id
                _ecs.add_component<controlable>(_ecs.entity_from_index(1), {client.GetId()});

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
                        control_system(_ecs, _event, _spriteManager);
                    }
                    ennemy_system(_ecs, _spriteManager, _window);
                    //client.receive();
                    sf::Packet sfp = client.WaitReceive();
                    if (sfp.getData() != NULL) { //cond doesn't work
                        std::string comparator;
                        sfp >> comparator;
                        std::cout << comparator << std::endl;
                        if (comparator == "new_client") {
                            int newCliId = 0;
                            sfp >> newCliId;
                            std::cout << newCliId << std::endl;
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

                        } else if (comparator == "old_client") {
                            int amount = 0;
                            int newCliId = 0;
                            sfp >> amount;
                            for (sfp >> newCliId; amount != 0; sfp >> newCliId, amount--) {
                                if (client.GetId() != newCliId) {
                                    std::cout << newCliId << std::endl;
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
                        } else {
                            std::cout << "unknow type" << std::endl;
                        }
                    } else {
                        std::cout << ">" << std::endl;
                    }

                    position_system(_ecs, _window, client);
                    draw_system(_ecs, _window);
                    _window.display();
                    collision_system(_ecs);
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
        int run(unsigned short port)
        {
//                _ecs.add_component<>
            Server server(port);
            sf::TcpSocket *socket;

            while (_window.isOpen()) { // run the program as long as the window is open
                _window.clear();
                if (server.selectorWait()) {
                    if (server.isNewConnection()) {
                        std::cout << "New Client" << std::endl;
                        server.accept();
                    }
                    socket = server.isNewMessage();
                    if (socket != nullptr)
                        server.receive(socket);
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
    };
};

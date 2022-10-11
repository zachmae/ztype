#include "Ecs.hpp"
#include "Component.hpp"

namespace GameStd {

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
}
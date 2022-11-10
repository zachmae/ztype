#include "ClientComponent.hpp"
#include <tuple>

namespace User {

    /**
     * @brief user config listing all components used by user
     *
     */
    struct client_config {
        using components_list = std::tuple<position,
                                            velocity,
                                            drawable,
                                            controlable,
                                            animation_basic,
                                            animation_adaptative,
                                            resizable,
                                            is_ship,
                                            collidable,
                                            is_background,
                                            is_ally,
                                            attack,
                                            health,
                                            is_boss,
                                            death_sfx,
                                            int>;
    };

}
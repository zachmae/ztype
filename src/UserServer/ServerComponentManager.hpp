#include "ServerComponent.hpp"
#include <tuple>

namespace User {

    /**
     * @brief user config listing all components used by user
     *
     */
    struct server_config {
        using components_list = std::tuple<position,
                                            velocity,
                                            controlable,
                                            resizable,
                                            is_ship,
                                            collidable,
                                            is_ally,
                                            attack,
                                            health,
                                            is_boss,
                                            int>;
    };

}
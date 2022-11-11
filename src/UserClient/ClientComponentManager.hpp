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
                                            clickable,
                                            clickable_sfx,
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
                                            value_score,
                                            text,
                                            is_score,
                                            is_text_button_dict,
                                            int>;
    };

}
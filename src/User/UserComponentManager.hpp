#include "UserComponent.hpp"
#include <tuple>

/**
 * @brief user config listing all components used by user
 *
 */
struct user_config {
    using components_list = std::tuple<position,
                                        velocity,
                                        drawable,
                                        controlable,
                                        clickable,
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
                                        int>;
};

#include "UserComponent.hpp"
#include <tuple>

struct user_config {
    using components_list = std::tuple<position,
                                        velocity,
                                        drawable,
                                        contralable>;
};

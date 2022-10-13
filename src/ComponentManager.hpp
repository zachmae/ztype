#include "Component.hpp"
#include <tuple>

struct config {
    using components_list = std::tuple<position,
                                        velocity,
                                        drawable,
                                        contralable>;
};

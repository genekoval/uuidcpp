#pragma once

#include "uuid.h"

#include <nlohmann/json.hpp>

namespace UUID {
    using json = nlohmann::json;

    inline auto from_json(const json& j, uuid& u) -> void {
        u = uuid(j.get<std::string>());
    }

    inline auto to_json(json& j, const uuid& u) -> void {
        j = json(u.string());
    }
}

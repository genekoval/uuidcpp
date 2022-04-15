#pragma once

#include <commline/commline>
#include <uuid++/uuid++>

namespace commline {
    template <>
    struct parser<UUID::uuid> {
        static auto parse(std::string_view argument) -> UUID::uuid {
            return UUID::uuid(argument);
        }
    };
}

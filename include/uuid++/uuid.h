#pragma once

#include <string_view>
#include <uuid/uuid.h>

namespace UUID {
    class uuid {
        /**
         * The length of a UUID's string representation.
         */
        static constexpr auto uuid_len =
            32 + // hex digits
            4 + // hyphens
            1; // terminating null character

        /**
         * Storage for the UUID's string representation.
         */
        char buffer[uuid_len];
        uuid_t value;

        auto parse(std::string_view str) -> void;

        auto unparse() -> void;
    public:
        uuid();

        uuid(const uuid& other);

        uuid(std::string_view str);

        auto operator=(const char* str) -> uuid&;

        auto clear() -> void;

        auto generate() -> void;

        auto is_null() const -> bool;

        auto string() const -> std::string_view;
    };
}

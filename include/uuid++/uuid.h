#pragma once

#include <uuid/uuid.h>

namespace UUID {
    class uuid {
        /**
         * The length of a UUID's string representation.
         *
         * Consists of:
         *      32 hex digits
         *      4 hyphens
         *      1 terminating null character
         */
        static constexpr auto uuid_len = 37;

        char str_buffer[uuid_len];
        uuid_t value;

        auto parse(const char* str) -> void;
        auto unparse() -> void;
    public:
        uuid() = default;
        uuid(const uuid& obj);
        uuid(const char* str);

        auto operator=(const char* str) -> uuid&;

        auto clear() -> void;

        auto generate() -> void;

        auto is_null() const -> bool;

        auto string() const -> const char*;
    };
}

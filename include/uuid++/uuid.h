#pragma once

#include <ostream>
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

        /**
         * Resets the value of this UUID to the NULL value.
         */
        auto clear() -> void;

        /**
         * Creates a new UUID and assigns it to this instance.
         */
        auto generate() -> void;

        auto parse(std::string_view str) -> void;

        auto unparse() -> void;
    public:
        /**
         * Initializes a new UUID with a randomly generated value.
         */
        uuid();

        /**
         * Creates a copy of the given UUID.
         */
        uuid(const uuid& other);

        uuid(uuid_t value);

        /**
         * Converts the given string into the binary representation.
         *
         * If the input is an invalid UUID, the resulting instance will be equal
         * to the NULL UUID.
         */
        uuid(std::string_view str);

        auto operator=(const char* str) -> uuid&;

        auto operator==(const uuid& other) const -> bool;

        auto operator<=>(const uuid& other) const -> std::strong_ordering;

        explicit operator bool() const noexcept;

        /**
         * Compares the value of this UUID to the NULL value.
         *
         * Returns true if the value is equal to the NULL UUID,
         * otherwise 0 is returned.
         */
        auto is_null() const -> bool;

        auto string() const -> std::string_view;
    };

    /**
     * Returns a UUID instance equal to the NULL UUID.
     */
    auto null() -> const uuid&;

    auto operator<<(std::ostream& os, const uuid& uu) -> std::ostream&;
}

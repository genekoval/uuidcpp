#pragma once

#include <array>
#include <ostream>
#include <span>
#include <string_view>
#include <uuid/uuid.h>

namespace UUID {
    /**
     * Number of bytes in a UUID's binary representation.
     */
    constexpr auto size = sizeof(uuid_t);

    /**
     * The length of a UUID's string representation.
     */
    constexpr auto strlen =
            32 + // hex digits
            4 + // hyphens
            1; // terminating null character

    class uuid {
        /**
         * Storage for the UUID's string representation.
         */
        std::array<char, strlen> str;

        /**
         * Storage for the UUID's binary representation.
         */
        uuid_t value;

        /**
         * Resets the value of this UUID to the NULL value.
         */
        auto clear() -> void;

        auto parse(std::string_view str) -> void;

        auto unparse() -> void;
    public:
        /**
         * Initializes a new UUID with a randomly generated value.
         */
        uuid();

        /**
         * Initializes a new UUID instance by using the value represented by
         * the specified array of bytes.
         */
        explicit uuid(const unsigned char* value);

        /**
         * Initializes a new UUID instance by using the value represented by
         * the specified read-only span of bytes.
         */
        explicit uuid(std::span<const unsigned char> bytes);

        /**
         * Converts the given character array into the binary representation.
         *
         * If the input is an invalid UUID, the resulting instance will be equal
         * to the NULL UUID.
         */
        uuid(const char* str);

        /**
         * Converts the given string into the binary representation.
         *
         * Throws a parse_error if parsing the string fails.
         */
        explicit uuid(std::string_view str);

        /**
         * Creates a copy of the given UUID.
         */
        uuid(const uuid& other);

        auto operator=(const char* str) -> uuid&;

        auto operator==(const uuid& other) const -> bool;

        auto operator<=>(const uuid& other) const -> std::strong_ordering;

        /**
         * Returns false if *this is equal to the NULL UUID, true otherwise.
         */
        explicit operator bool() const noexcept;

        operator std::string_view() const noexcept;

        /**
         * Returns the UUID as bytes.
         */
        auto bytes() const -> std::span<const unsigned char>;

        /**
         * Compares the value of this UUID to the NULL value.
         *
         * Returns true if the value is equal to the NULL UUID,
         * otherwise 0 is returned.
         */
        auto is_null() const -> bool;

        /**
         * Returns a string created from the UUID,
         * such as "d8875077-b44c-4be5-9de4-1234130702ce".
         */
        auto string() const -> std::string_view;
    };

    class parse_error : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    /**
     * Returns a new randomly generated UUID.
     */
    auto generate() -> uuid;

    /**
     * Returns a UUID instance equal to the NULL UUID.
     */
    auto null() -> const uuid&;

    auto operator<<(std::ostream& os, const uuid& uu) -> std::ostream&;
}

#pragma once

#include <array>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

namespace UUID {
    /**
     * Number of bytes in a UUID's binary representation.
     */
    constexpr auto size = std::size_t(16);

    /**
     * The length of a UUID's string representation.
     */
    constexpr auto strlen =
            size * 2 + // hex digits
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
        std::array<unsigned char, size> value;
    public:
        /**
         * Initializes a new UUID equal to the NULL UUID.
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
        explicit uuid(const char* str);

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

    struct parse_error : std::runtime_error {
        parse_error(std::string_view str);
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

    auto parse(std::string_view str) -> std::optional<uuid>;
}

namespace std {
    template <>
    struct hash<UUID::uuid> {
        auto operator()(const UUID::uuid& uuid) const noexcept -> size_t;
    };
}

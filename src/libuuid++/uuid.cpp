#include <uuid++/uuid.h>

namespace {
    auto create_null_uuid() -> UUID::uuid {
        uuid_t result;
        uuid_clear(result);
        return UUID::uuid(result);
    }
}

namespace UUID {
    uuid::uuid() : uuid(null()) {}

    uuid::uuid(const char* str) : uuid(std::string_view(str)) {}

    uuid::uuid(std::string_view str) {
        parse(str);
    }

    uuid::uuid(const unsigned char* value) {
        uuid_copy(this->value, value);
        unparse();
    }

    uuid::uuid(std::span<const unsigned char> bytes) : uuid(bytes.data()) {}

    uuid::uuid(const uuid& other) {
        uuid_copy(value, other.value);
        str = other.str;
    }

    auto uuid::operator=(const char* str) -> uuid& {
        parse(str);
        return *this;
    }

    auto uuid::operator==(const uuid& other) const -> bool {
        return uuid_compare(value, other.value) == 0;
    }

    auto uuid::operator<=>(const uuid& other) const -> std::strong_ordering {
        const auto result = uuid_compare(value, other.value);

        if (result < 0) return std::strong_ordering::less;
        if (result > 0) return std::strong_ordering::greater;

        return std::strong_ordering::equal;
    }

    uuid::operator bool() const noexcept {
        return !is_null();
    }

    uuid::operator std::string_view() const noexcept {
        return string();
    }

    auto uuid::bytes() const -> std::span<const unsigned char> {
        return value;
    }

    auto uuid::clear() -> void {
        uuid_clear(value);
        unparse();
    }

    auto uuid::is_null() const -> bool {
        return uuid_is_null(value) == 1;
    }

    auto uuid::parse(std::string_view str) -> void {
        if (uuid_parse_range(str.data(), str.end(), value) == 0) {
            // Use the 'unparse' function instead of copying the input string
            // in order to keep the string representations consistent.
            // If the input string contains uppercase letters, but default
            // behavior is to use lowercase letters, then we want this instance
            // to contain the lowercased representation.
            unparse();
        }
        // If parsing fails, clear this instance so that it will be equal to
        // the NULL UUID.
        else clear();
    }

    auto uuid::string() const -> std::string_view {
        // Do not include the terminating null character.
        return std::string_view(str.data(), str.size() - 1);
    }

    auto uuid::unparse() -> void {
        uuid_unparse(value, str.data());
    }

    auto null() -> const uuid& {
        static auto instance = create_null_uuid();
        return instance;
    }

    auto operator<<(std::ostream& os, const UUID::uuid& uu) -> std::ostream& {
        return os << uu.string();
    }

    auto generate() -> uuid {
        uuid_t value;
        uuid_generate(value);
        return uuid(value);
    }
}

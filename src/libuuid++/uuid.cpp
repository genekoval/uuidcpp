#include <uuid++/uuid.h>

#include <cstring>

namespace {
    auto create_null_uuid() -> UUID::uuid {
        uuid_t result;
        uuid_clear(result);
        return UUID::uuid(result);
    }
}

namespace UUID {
    uuid::uuid() {
        generate();
    }

    uuid::uuid(const uuid& other) {
        uuid_copy(value, other.value);
        unparse();
    }

    uuid::uuid(std::string_view str) {
        // Clear the UUID first so that it is null if parsing fails.
        clear();
        parse(str);
    }

    uuid::uuid(uuid_t value) {
        uuid_copy(this->value, value);
        unparse();
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

    auto uuid::clear() -> void {
        uuid_clear(value);
        unparse();
    }

    auto uuid::generate() -> void {
        uuid_generate(value);
        unparse();
    }

    auto uuid::is_null() const -> bool {
        return uuid_is_null(value) == 1;
    }

    auto uuid::parse(std::string_view str) -> void {
        uuid_parse_range(str.data(), str.end(), value);
        str.copy(buffer, str.size());
    }

    auto uuid::string() const -> std::string_view {
        return buffer;
    }

    auto uuid::unparse() -> void {
        uuid_unparse(value, buffer);
    }

    auto null() -> const uuid& {
        static auto instance = create_null_uuid();
        return instance;
    }
}

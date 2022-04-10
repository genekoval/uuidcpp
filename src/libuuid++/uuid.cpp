#include <uuid++/uuid.h>

#include <cstring>

namespace UUID {
    uuid::uuid() {
        generate();
    }

    uuid::uuid(const uuid& other) {
        uuid_copy(value, other.value);
        unparse();
    }

    uuid::uuid(std::string_view str) {
        parse(str);
    }

    auto uuid::operator=(const char* str) -> uuid& {
        parse(str);
        return *this;
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
        uuid_parse_range(str.data(), str.end() - 1, value);
        str.copy(buffer, str.size());
    }

    auto uuid::string() const -> std::string_view {
        return buffer;
    }

    auto uuid::unparse() -> void {
        uuid_unparse(value, buffer);
    }
}

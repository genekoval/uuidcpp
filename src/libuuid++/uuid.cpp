#include <uuid++/uuid.h>

#include <cstring>

namespace UUID {
    uuid::uuid(const uuid& obj) {
        uuid_copy(value, obj.value);
        unparse();
    }

    uuid::uuid(const char* str) { parse(str); }

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

    auto uuid::is_null() const -> bool { return uuid_is_null(value) == 1; }

    auto uuid::parse(const char* str) -> void {
        uuid_parse(str, value);
        std::strcpy(str_buffer, str);
    }

    auto uuid::string() const -> const char* { return str_buffer; }

    auto uuid::unparse() -> void { uuid_unparse(value, str_buffer); }
}

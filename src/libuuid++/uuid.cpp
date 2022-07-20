#include <uuid++/uuid.h>

#include <fmt/core.h>
#include <sstream>
#include <uuid/uuid.h>

namespace UUID {
    uuid::uuid() : uuid(null()) {}

    uuid::uuid(const unsigned char* value) {
        uuid_copy(this->value.data(), value);
        uuid_unparse_lower(this->value.data(), str.data());
    }

    uuid::uuid(std::span<const unsigned char> bytes) : uuid(bytes.data()) {}

    uuid::uuid(const char* str) : uuid(std::string_view(str)) {}

    uuid::uuid(std::string_view str) {
        if (str.size() != strlen - 1) throw parse_error(str);

        for (auto i = 0u; i < str.size(); ++i) {
            this->str[i] = std::tolower(str[i]);
        }

        this->str[str.size()] = '\0';

        const auto* data = this->str.data();

        if (uuid_parse_range(data, data + str.size(), value.data()) != 0) {
            throw parse_error(str);
        }
    }

    uuid::uuid(const uuid& other) {
        std::memcpy(value.data(), other.value.data(), size);
        std::memcpy(str.data(), other.str.data(), strlen);
    }

    auto uuid::operator=(const char* str) -> uuid& {
        parse(str);
        return *this;
    }

    auto uuid::operator==(const uuid& other) const -> bool {
        return uuid_compare(value.data(), other.value.data()) == 0;
    }

    auto uuid::operator<=>(const uuid& other) const -> std::strong_ordering {
        const auto result = uuid_compare(value.data(), other.value.data());

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

    auto uuid::is_null() const -> bool {
        return uuid_is_null(value.data()) == 1;
    }

    auto uuid::string() const -> std::string_view {
        // Do not include the terminating null character.
        return std::string_view(str.data(), str.size() - 1);
    }

    parse_error::parse_error(std::string_view str) :
        runtime_error(fmt::format("invalid UUID: {}", str))
    {}

    auto null() -> const uuid& {
        static const auto instance = [] {
            auto value = std::array<unsigned char, size>();
            uuid_clear(value.data());
            return uuid(value);
        }();

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

    auto parse(std::string_view str) -> std::optional<uuid> {
        try {
            return uuid(str);
        }
        catch (const parse_error& ex) {
            return {};
        }
    }
}

namespace std {
    auto hash<UUID::uuid>::operator()(
        const UUID::uuid& uuid
    ) const noexcept -> size_t {
        return hash<std::string_view>{}(uuid.string());
    }
}

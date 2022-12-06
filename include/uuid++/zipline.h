#pragma once

#include <uuid++/uuid++>
#include <zipline/zipline>

namespace zipline {
    template <io::reader Reader>
    struct decoder<UUID::uuid, Reader> {
        static auto decode(Reader& reader) -> ext::task<UUID::uuid> {
            auto bytes = std::array<unsigned char, UUID::size>();
            co_await reader.read(bytes.data(), bytes.size());

            const auto uuid = UUID::uuid(bytes);
            TIMBER_TRACE("decode uuid: {}", uuid);

            co_return uuid;
        }
    };

    template <io::writer Writer>
    struct encoder<UUID::uuid, Writer> {
        static auto encode(
            const UUID::uuid& uuid,
            Writer& writer
        ) -> ext::task<> {
            TIMBER_TRACE("encode uuid: {}", uuid);

            const auto bytes = uuid.bytes();
            co_await writer.write(bytes.data(), bytes.size());
        }
    };
}

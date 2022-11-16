#pragma once

#include <uuid++/uuid++>
#include <zipline/zipline>

namespace zipline {
    template <typename Socket>
    struct coder<Socket, UUID::uuid> {
        static auto decode(Socket& socket) -> ext::task<UUID::uuid> {
            auto bytes = std::array<unsigned char, UUID::size>();
            co_await socket.read(bytes.data(), bytes.size());

            const auto uuid = UUID::uuid(bytes);
            TIMBER_TRACE("decode uuid: {}", uuid);

            co_return uuid;
        }

        static auto encode(
            Socket& socket,
            const UUID::uuid& uuid
        ) -> ext::task<> {
            TIMBER_TRACE("encode uuid: {}", uuid);

            const auto bytes = uuid.bytes();
            co_await socket.write(bytes.data(), bytes.size());
        }
    };
}

#include <uuid++/uuid++>
#include <zipline/zipline>

namespace zipline {
    template <typename Socket>
    struct transfer<Socket, UUID::uuid> {
        static auto read(Socket& socket) -> UUID::uuid {
            auto bytes = std::array<unsigned char, UUID::size>();
            socket.read(bytes.data(), bytes.size());
            return UUID::uuid(bytes);
        }

        static auto write(Socket& socket, const UUID::uuid& uuid) -> void {
            const auto bytes = uuid.bytes();
            socket.write(bytes.data(), bytes.size());
        }
    };
}

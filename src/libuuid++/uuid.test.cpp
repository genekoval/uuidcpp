#include <uuid++/uuid++>

#include <gtest/gtest.h>

using namespace std::literals;

namespace {
    constexpr auto string = "cbb3c3d4-a822-4380-a98a-923473870992"sv;

    const auto uuid1 = UUID::uuid(string);
    const auto uuid2 = UUID::uuid("07e32d65-8aae-4a2f-8991-43644604b5d7");
}

TEST(UUIDTest, Assignment) {
    auto uuid = UUID::null();
    ASSERT_TRUE(uuid.is_null());

    uuid = uuid1;
    ASSERT_EQ(uuid1, uuid);
}

TEST(UUIDTest, Bool) {
    ASSERT_TRUE(uuid1);
    ASSERT_FALSE(UUID::null());
}

TEST(UUIDTest, Bytes) {
    const auto bytes = uuid1.bytes();
    ASSERT_EQ(UUID::size, bytes.size());

    const auto uuid = UUID::uuid(bytes);
    ASSERT_EQ(uuid1, uuid);
}

TEST(UUIDTest, Comparison) {
    ASSERT_EQ(uuid1, uuid1);
    ASSERT_EQ(uuid1, UUID::uuid(string));
    ASSERT_NE(uuid1, uuid2);

    ASSERT_TRUE(uuid2 < uuid1);
    ASSERT_TRUE(UUID::null() < uuid2);
}

TEST(UUIDTest, Default) {
    const auto uuid = UUID::uuid();
    ASSERT_TRUE(uuid.is_null());
}

TEST(UUIDTest, Parse) {
    ASSERT_FALSE(UUID::uuid("hello"));

    const auto str = std::string(string) + "2";
    ASSERT_FALSE(UUID::uuid(str));

    const auto substr = str.substr(0, str.size() - 1);
    const auto uuid = UUID::uuid(substr);
    ASSERT_TRUE(uuid);
    ASSERT_EQ(uuid1, uuid);
}

TEST(UUIDTest, Stream) {
    auto os = std::ostringstream();
    os << uuid1;
    const auto result = os.str();

    ASSERT_EQ(string, result);
}

TEST(UUIDTest, String) {
    ASSERT_EQ(string, uuid1.string());
}

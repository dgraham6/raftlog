#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <cstddef>
#include "raftlog/log/log.hpp"
#include "raftlog/log/segment.hpp"
#include <iostream>

using namespace raftlog::log;

TEST_CASE("put_uint32_t", "[log]")
{
    std::vector<std::byte> v;
    put_u32_le(v, 2);
    REQUIRE((static_cast<unsigned char>(v[0]) == 0b0010));
}

TEST_CASE("get_uint32_t_467", "[log]")
{
    std::vector<std::byte> v;
    put_u32_le(v, 467);
    uint32_t temp = get_u32_le(v, 0);
    REQUIRE((temp == 467));
}

TEST_CASE("get_uint32_t", "[log]")
{
    std::vector<std::byte> v;
    put_u32_le(v, 2);
    uint32_t temp = get_u32_le(v, 0);
    REQUIRE((temp == 2));
    put_u32_le(v, 467);
    temp = get_u32_le(v, 4);
    REQUIRE((temp == 467));
    put_u32_le(v, 1104745215);
    temp = get_u32_le(v, 8);
    REQUIRE((temp == 1104745215));
}

TEST_CASE("encoder size check", "[log]")
{
    std::vector<std::byte> temp(2);
    std::vector<std::byte> encoded = EncodeRecord(temp);
    REQUIRE(encoded.size() == temp.size() + 8);
}

TEST_CASE("decoder happy", "[log]")
{
    std::vector<std::byte> temp(2);
    std::vector<std::byte> encoded = EncodeRecord(temp);
    std::optional<DecodeResponse> resp = DecodeRecord(encoded);
    REQUIRE(resp);
}

TEST_CASE("decoder bad", "[log]")
{
    std::vector<std::byte> temp(2);
    std::vector<std::byte> encoded = EncodeRecord(temp);
    encoded.pop_back();
    std::optional<DecodeResponse> resp = DecodeRecord(encoded);
    REQUIRE(!resp);
    encoded = EncodeRecord(temp);
    encoded[2] = std::byte{0b0101};
    resp = DecodeRecord(encoded);
    REQUIRE(!resp);
    encoded = EncodeRecord(temp);
    encoded[5] = std::byte{0b0101};
    resp = DecodeRecord(encoded);
    REQUIRE(!resp);
    encoded = EncodeRecord(temp);
    encoded[8] = std::byte{0b0101};
    resp = DecodeRecord(encoded);
    REQUIRE(!resp);
    encoded = EncodeRecord(temp);
    for (int i = 0; i < 4; ++i)
    {
        encoded.pop_back();
    }
    resp = DecodeRecord(encoded);
    REQUIRE(!resp);
}

TEST_CASE("append", "[log]")
{
    Segment s(std::filesystem::temp_directory_path() / "append_test.log", 0);
    std::vector<std::byte> p(1, std::byte{0x61});
    std::uint64_t res = s.Append(p);
    REQUIRE(res == 0);
    res = s.Append(p);
    REQUIRE(res == 1);
}
TEST_CASE("read", "[log]")
{
    Segment s(std::filesystem::temp_directory_path() / "read_test.log", 0);
    std::vector<std::byte> p(1, std::byte{0x61});
    s.Append(p);
    std::optional<Record> r = s.Read(0);
    REQUIRE(r);
    REQUIRE(r->payload == p);
}

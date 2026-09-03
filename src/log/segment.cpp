#include "raftlog/log/segment.hpp"
#include <zlib.h>
#include <iostream>

namespace raftlog::log
{
    // pushs uint32_t into vector of bytes little endian
    void put_u32_le(std::vector<std::byte> &out, std::uint32_t value)
    {
        for (int i = 0; i < 4; ++i)
        {
            unsigned char b = (value & 0xFF);
            out.push_back(std::byte{b});
            value >>= 8;
        }
    }
    // gets uint32_t from vector of bytes little endian
    // assumes in.size() >= 4
    uint32_t get_u32_le(const std::vector<std::byte> &in, int start)
    {
        uint32_t res = 0;
        for (int i = 3; i >= 0; --i)
        {
            res |= static_cast<unsigned char>((in[start + i])) << (8 * i);
        }
        return res;
    }

    // encode bytes into crc + length + type
    std::vector<std::byte> EncodeRecord(std::vector<std::byte> payload)
    {
        uint32_t crc = crc32(0L, Z_NULL, 0);
        crc = crc32(crc, reinterpret_cast<unsigned char *>(payload.data()), payload.size());
        std::vector<std::byte> encoded;
        encoded.reserve(8 + payload.size());
        put_u32_le(encoded, crc);
        put_u32_le(encoded, payload.size());
        encoded.insert(encoded.end(), payload.begin(), payload.end());
        return encoded;
    }
    std::optional<DecodeResponse> DecodeRecord(std::vector<std::byte> record)
    {
        if (record.size() < 8)
        {
            return std::nullopt;
        }

        uint32_t crc = crc32(0L, Z_NULL, 0);
        uint32_t original_crc = get_u32_le(record, 0);
        uint32_t length = get_u32_le(record, 4);
        uint32_t rsize = record.size() - 8;

        if (rsize != length)
        {
            return std::nullopt;
        }

        crc = crc32(crc, reinterpret_cast<unsigned char *>(record.data()) + 8, length);

        if (crc != original_crc)
        {
            return std::nullopt;
        }

        std::vector<std::byte> res(record.begin() + 4, record.end());
        return DecodeResponse{res};
    }

    Segment::Segment(std::filesystem::path path, std::uint64_t base_offset)
        : path_(std::move(path)), base_offset_(base_offset) {}

    std::uint64_t Segment::Append(std::vector<std::byte> payload)
    {
        (void)payload;
        // TODO(phase 1): write length-prefixed record + CRC, return new offset.
        return 0;
    }

    std::optional<Record> Segment::Read(std::uint64_t offset) const
    {
        (void)offset;
        // TODO(phase 1): seek via index, verify CRC, return the record.
        return std::nullopt;
    }

    std::size_t Segment::SizeBytes() const
    {
        // TODO(phase 1): on-disk size, used to decide when to roll.
        return 0;
    }

} // namespace raftlog::log

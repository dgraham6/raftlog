#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace raftlog::log
{
    struct DecodeResponse
    {
        std::vector<std::byte> payload;
    };

    void put_u32_le(std::vector<std::byte> &out, std::uint32_t value);
    uint32_t get_u32_le(const std::vector<std::byte> &in, int start);
    std::vector<std::byte> EncodeRecord(std::vector<std::byte> payload);
    std::optional<DecodeResponse> DecodeRecord(std::vector<std::byte> record);

    struct Record
    {
        std::uint64_t offset;
        std::vector<std::byte> payload;
    };

    // One append-only file on disk: length-prefixed, CRC-checked records.
    // Phase 1: define the on-disk format and get append/read working.
    class Segment
    {
    public:
        Segment(std::filesystem::path path, std::uint64_t base_offset);

        std::uint64_t Append(std::vector<std::byte> payload);
        std::optional<Record> Read(std::uint64_t offset) const;
        std::size_t SizeBytes() const;

        std::uint64_t base_offset() const { return base_offset_; }

    private:
        std::filesystem::path path_;
        std::uint64_t base_offset_;
    };

} // namespace raftlog::log

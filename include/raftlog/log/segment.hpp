#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace raftlog::log {

struct Record {
    std::uint64_t offset;
    std::vector<std::byte> payload;
};

// One append-only file on disk: length-prefixed, CRC-checked records.
// Phase 1: define the on-disk format and get append/read working.
class Segment {
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

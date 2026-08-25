#include "raftlog/log/segment.hpp"

namespace raftlog::log {

Segment::Segment(std::filesystem::path path, std::uint64_t base_offset)
    : path_(std::move(path)), base_offset_(base_offset) {}

std::uint64_t Segment::Append(std::vector<std::byte> payload) {
    (void)payload;
    // TODO(phase 1): write length-prefixed record + CRC, return new offset.
    return 0;
}

std::optional<Record> Segment::Read(std::uint64_t offset) const {
    (void)offset;
    // TODO(phase 1): seek via index, verify CRC, return the record.
    return std::nullopt;
}

std::size_t Segment::SizeBytes() const {
    // TODO(phase 1): on-disk size, used to decide when to roll.
    return 0;
}

} // namespace raftlog::log

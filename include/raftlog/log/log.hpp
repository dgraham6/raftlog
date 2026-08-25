#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

#include "raftlog/log/segment.hpp"

namespace raftlog::log {

// A single partition: an ordered sequence of segments rolled by size.
// Phase 1.
class Log {
public:
    explicit Log(std::filesystem::path directory);

    std::uint64_t Append(std::vector<std::byte> payload);
    std::optional<Record> Read(std::uint64_t offset) const;

    // Restore in-memory state (active segment, next offset) from disk.
    // This is the crash-recovery path -- get it right before anything else.
    void Recover();

private:
    std::filesystem::path directory_;
    std::vector<Segment> segments_;
    std::uint64_t next_offset_ = 0;
};

} // namespace raftlog::log

#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>

namespace raftlog::log {

// Sparse offset -> byte-position index for a segment, so reads don't
// require a linear scan. Phase 1.
class Index {
public:
    explicit Index(std::filesystem::path path);

    void Append(std::uint64_t offset, std::uint64_t position);
    std::optional<std::uint64_t> Lookup(std::uint64_t offset) const;

private:
    std::filesystem::path path_;
};

} // namespace raftlog::log

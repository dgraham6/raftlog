#include "raftlog/log/index.hpp"

namespace raftlog::log {

Index::Index(std::filesystem::path path) : path_(std::move(path)) {}

void Index::Append(std::uint64_t offset, std::uint64_t position) {
    (void)offset;
    (void)position;
    // TODO(phase 1): append a sparse (offset, position) entry.
}

std::optional<std::uint64_t> Index::Lookup(std::uint64_t offset) const {
    (void)offset;
    // TODO(phase 1): binary search the sparse index, return nearest <= offset.
    return std::nullopt;
}

} // namespace raftlog::log

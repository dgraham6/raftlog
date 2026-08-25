#include "raftlog/log/log.hpp"

namespace raftlog::log
{

    Log::Log(std::filesystem::path directory) : directory_(std::move(directory)) {}

    std::uint64_t Log::Append(std::vector<std::byte> payload)
    {
        (void)payload;
        // TODO(phase 1): append to the active segment, rolling if it's full.
        return 0;
    }

    std::optional<Record> Log::Read(std::uint64_t offset) const
    {
        (void)offset;
        // TODO(phase 1): find the segment containing offset, delegate to it.
        return std::nullopt;
    }

    void Log::Recover()
    {
        // TODO(phase 1): scan directory_ for existing segments, rebuild
        // next_offset_ and the active segment from what's on disk.
    }

} // namespace raftlog::log

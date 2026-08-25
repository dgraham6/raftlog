#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace raftlog::broker {

// Phase 2: hand-rolled wire format, not protobuf -- the framing is the point.
struct ProduceRequest {
    std::string topic;
    std::uint32_t partition;
    std::vector<std::byte> payload;
};

struct ProduceResponse {
    std::uint64_t offset;
};

struct FetchRequest {
    std::string topic;
    std::uint32_t partition;
    std::uint64_t offset;
    std::uint32_t max_bytes;
};

struct FetchResponse {
    std::vector<std::byte> data;
};

} // namespace raftlog::broker

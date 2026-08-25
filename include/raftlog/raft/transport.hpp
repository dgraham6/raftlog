#pragma once

#include <cstdint>

#include "raftlog/raft/rpc.hpp"

namespace raftlog::raft {

using NodeId = std::uint64_t;

// Abstract network so Raft can run against a fake, fault-injecting
// implementation in tests before ever touching a real socket.
// Getting this abstraction right comes before anything else in Phase 4.
class Transport {
public:
    virtual ~Transport() = default;

    virtual RequestVoteResponse SendRequestVote(NodeId to, const RequestVoteRequest& req) = 0;
    virtual AppendEntriesResponse SendAppendEntries(NodeId to, const AppendEntriesRequest& req) = 0;
};

} // namespace raftlog::raft

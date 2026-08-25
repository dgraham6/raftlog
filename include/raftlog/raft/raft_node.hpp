#pragma once

#include <cstdint>
#include <vector>

#include "raftlog/raft/rpc.hpp"
#include "raftlog/raft/transport.hpp"

namespace raftlog::raft {

enum class Role { Follower, Candidate, Leader };

// Phase 4: leader election -> log replication -> persistence -> snapshots.
// Build and test this against a fake Transport before wiring in real sockets.
class RaftNode {
public:
    RaftNode(NodeId id, std::vector<NodeId> peers, Transport& transport);

    RequestVoteResponse HandleRequestVote(const RequestVoteRequest& req);
    AppendEntriesResponse HandleAppendEntries(const AppendEntriesRequest& req);

    // Drives timeouts / heartbeats. Call this on a timer.
    void Tick();

    Role role() const { return role_; }
    Term current_term() const { return current_term_; }

private:
    NodeId id_;
    std::vector<NodeId> peers_;
    Transport& transport_;

    Role role_ = Role::Follower;
    Term current_term_ = 0;
    std::vector<LogEntry> log_;
};

} // namespace raftlog::raft

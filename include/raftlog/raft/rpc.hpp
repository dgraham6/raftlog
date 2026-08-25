#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace raftlog::raft {

using Term = std::uint64_t;

struct LogEntry {
    Term term;
    std::vector<std::byte> command;
};

struct RequestVoteRequest {
    Term term;
    std::uint64_t candidate_id;
    std::uint64_t last_log_index;
    Term last_log_term;
};

struct RequestVoteResponse {
    Term term;
    bool vote_granted;
};

struct AppendEntriesRequest {
    Term term;
    std::uint64_t leader_id;
    std::uint64_t prev_log_index;
    Term prev_log_term;
    std::vector<LogEntry> entries;
    std::uint64_t leader_commit;
};

struct AppendEntriesResponse {
    Term term;
    bool success;
};

} // namespace raftlog::raft

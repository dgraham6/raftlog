#include "raftlog/raft/raft_node.hpp"

namespace raftlog::raft {

RaftNode::RaftNode(NodeId id, std::vector<NodeId> peers, Transport& transport)
    : id_(id), peers_(std::move(peers)), transport_(transport) {}

RequestVoteResponse RaftNode::HandleRequestVote(const RequestVoteRequest& req) {
    (void)req;
    // TODO(phase 4): grant/deny vote per the Raft election rules.
    return {current_term_, false};
}

AppendEntriesResponse RaftNode::HandleAppendEntries(const AppendEntriesRequest& req) {
    (void)req;
    // TODO(phase 4): log matching, append new entries, advance commit index.
    return {current_term_, false};
}

void RaftNode::Tick() {
    // TODO(phase 4): election timeout -> become candidate; leader -> send
    // heartbeats.
}

} // namespace raftlog::raft

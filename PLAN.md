# raftlog — plan

A Kafka-style replicated log, hand-written in C++ to actually learn the
internals of both the storage engine and Raft consensus. Two tracks that
converge: storage/broker (Track A) and Raft (Track B), built and tested
independently before being wired together.

Reference material worth reading directly rather than secondhand:
- Raft paper: "In Search of an Understandable Consensus Algorithm"
- Kafka's own design docs / Jay Kreps' "The Log" post

---

## Phase 0 — Foundations
- [ ] CMake project, C++20
- [ ] Catch2 wired up via FetchContent
- [ ] Structured logging with node-id/term/index fields (needed before
      Raft debugging starts, not after)

## Phase 1 — Log storage engine (Track A)
- [ ] Segment file format: length-prefixed records + CRC
- [ ] Segment rolling at a size threshold
- [ ] Sparse offset index (offset → byte position)
- [ ] Multiple partitions as directories; topic = set of partitions
- [ ] Fetch-from-offset API with a max-bytes cap
- [ ] **Test focus:** crash mid-write, verify recovery truncates cleanly
      instead of reading a torn record

## Phase 2 — Wire protocol + broker (Track A)
- [ ] Hand-rolled binary protocol (Produce/Fetch) — no protobuf, the
      framing is the point
- [ ] Thread-per-connection TCP server
- [ ] Minimal C++ client for end-to-end produce/consume
- [ ] **Test focus:** concurrent producers on the same partition

## Phase 3 — Consumer groups
- [ ] Offset commits stored as records in an internal log (reuse Phase 1,
      same mechanism Kafka itself uses)
- [ ] Simplified group coordinator: partition assignment + heartbeats
- [ ] Skip full incremental rebalancing at first — this phase is more
      mechanical than deep, don't over-invest here

## Phase 4 — Raft, standalone (Track B)
Build from the paper, not a summary. This is the deep-learning core of
the project — budget the most time here.
- [ ] Leader election only (terms, votes, randomized timeouts), tested
      against a fake `Transport` that can drop/delay/duplicate messages
- [ ] Log replication (AppendEntries, log matching, commit index)
- [ ] Persistence (currentTerm/votedFor/log survive a crash) + recovery
- [ ] Log compaction / snapshotting
- [ ] **Test focus:** partition the fake network mid-write, kill the
      leader mid-replication, restart nodes with stale logs — assert
      safety properties (never two leaders in one term, committed
      entries never lost), not just the happy path

## Phase 5 — Merge the tracks
- [ ] One partition backed by one Raft group; each committed Raft entry
      becomes an append to the Phase 1 storage engine (Redpanda-style —
      real Kafka only uses Raft for KRaft metadata, not partition data,
      but replicating actual data is more educational)
- [ ] Swap the fake transport for real sockets — expect "worked in the
      simulator" bugs to surface here

## Phase 6 — Failover behavior
- [ ] Client-visible leader changes
- [ ] Produce acks semantics (ack after local write vs. after Raft
      commit — maps to Kafka's acks=1 vs acks=all)
- [ ] Multi-partition = multi-Raft-group

## Stretch goals
- [ ] KRaft-style separate metadata quorum (topic creation, membership)
      as its own Raft group
- [ ] Key-based log compaction (not just time/size retention) 
- [ ] A small TLA+ spec for the Raft safety properties
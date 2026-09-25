# raftlog

A hand-written, learning-focused C++ project combining two things from
*Designing Data-Intensive Applications* and the Kafka ecosystem:

1. A Kafka-style append-only log / broker — storage engine, partitions,
   wire protocol, consumer groups.
2. A from-scratch Raft implementation, used the way Redpanda does it:
   replicating actual partition data, not just cluster metadata.

Inspired after read DDIA, and wanting to hand code after work for my sanity (outside of leetcode).

See [PLAN.md](PLAN.md) for the phased roadmap
## Build

```
cmake -B build
cmake --build build
ctest --test-dir build
```

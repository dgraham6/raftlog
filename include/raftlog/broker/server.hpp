#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "raftlog/log/log.hpp"

namespace raftlog::broker {

// Phase 2: thread-per-connection TCP server speaking the protocol in
// protocol.hpp, backed by the partition logs in raftlog::log.
class Server {
public:
    explicit Server(std::uint16_t port);

    void Run();
    void Stop();

private:
    std::uint16_t port_;
    std::unordered_map<std::string, log::Log> partitions_;
};

} // namespace raftlog::broker

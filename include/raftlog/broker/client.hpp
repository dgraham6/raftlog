#pragma once

#include <cstdint>
#include <string>

#include "raftlog/broker/protocol.hpp"

namespace raftlog::broker {

// Phase 2: minimal client so you can produce/consume end-to-end.
class Client {
public:
    Client(std::string host, std::uint16_t port);

    ProduceResponse Produce(const ProduceRequest& req);
    FetchResponse Fetch(const FetchRequest& req);

private:
    std::string host_;
    std::uint16_t port_;
};

} // namespace raftlog::broker

#include "raftlog/broker/server.hpp"

namespace raftlog::broker {

Server::Server(std::uint16_t port) : port_(port) {}

void Server::Run() {
    // TODO(phase 2): bind port_, accept connections, dispatch one thread
    // per connection to handle Produce/Fetch requests against partitions_.
}

void Server::Stop() {
    // TODO(phase 2): close listening socket, join connection threads.
}

} // namespace raftlog::broker

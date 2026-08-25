#include "raftlog/broker/client.hpp"

namespace raftlog::broker {

Client::Client(std::string host, std::uint16_t port)
    : host_(std::move(host)), port_(port) {}

ProduceResponse Client::Produce(const ProduceRequest& req) {
    (void)req;
    // TODO(phase 2): serialize req, send over the socket, parse response.
    return {};
}

FetchResponse Client::Fetch(const FetchRequest& req) {
    (void)req;
    // TODO(phase 2): serialize req, send over the socket, parse response.
    return {};
}

} // namespace raftlog::broker

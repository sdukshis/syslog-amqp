#include "Endpoint.h"

Endpoint::Endpoint(const std::string &addr, port_t port)
        : addr_{addr}
        , port_{port} { }

Endpoint & Endpoint::operator=(const Endpoint &other) {
    Endpoint tmp{other};
    swap(tmp);
    return *this;
}

Endpoint & Endpoint::operator=(Endpoint &&other) {
    addr_ = std::move(other.addr_);
    port_ = other.port_;
    return *this;
}

void Endpoint::swap(Endpoint &other) {
    std::swap(addr_, other.addr_);
    std::swap(port_, other.port_);
}

std::string Endpoint::toString() const {
    return (addr_.empty() ? "*" : addr_) + ':' + std::to_string(port_);
}
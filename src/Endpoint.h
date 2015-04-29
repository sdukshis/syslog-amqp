#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <string>
#include <ostream>
#include <utility>

class Endpoint {
 public:
    using port_t = unsigned short;

    Endpoint() = delete;

    Endpoint(const std::string &addr, port_t);

    Endpoint(const Endpoint &) = default;

    Endpoint(Endpoint &&) = default;

    Endpoint & operator=(const Endpoint &);

    Endpoint & operator=(Endpoint &&);

    void swap(Endpoint &);

    const std::string & getAddr() const;

    port_t getPort() const;

    friend bool operator==(const Endpoint &, const Endpoint &);

    friend std::ostream & operator<<(std::ostream &, const Endpoint &);

 private:
    std::string addr_;
    port_t port_;
};  // class Endpoint

inline Endpoint::Endpoint(const std::string &addr, port_t port)
    : addr_{addr}
    , port_{port} { }

inline Endpoint & Endpoint::operator=(const Endpoint &other) {
    Endpoint tmp{other};
    swap(tmp);
    return *this;
}

inline Endpoint & Endpoint::operator=(Endpoint &&other) {
    addr_ = std::move(other.addr_);
    port_ = other.port_;
    return *this;
}

inline void Endpoint::swap(Endpoint &other) {
    std::swap(addr_, other.addr_);
    std::swap(port_, other.port_);
}

inline const std::string & Endpoint::getAddr() const {
    return addr_;
}

inline Endpoint::port_t Endpoint::getPort() const {
    return port_;
}

inline bool operator==(const Endpoint &lhs, const Endpoint &rhs) {
    return lhs.addr_ == rhs.addr_ &&
           lhs.port_ == rhs.port_;
}

inline bool operator!=(const Endpoint &lhs, const Endpoint &rhs) {
    return !(lhs == rhs);
}

inline std::ostream & operator<<(std::ostream &stream, const Endpoint &e) {
    return stream << (e.addr_.empty() ? "*" : e.addr_) << ":" << e.port_;
}


#endif  // ENDPOINT_H

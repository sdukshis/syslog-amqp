#include "Message.h"
#include "UDPListener.h"

#include <asio.hpp>
int main(int argc, char const *argv[])
{
    asio::io_service io_service;
    UDPListener udp_listener(Endpoint("0.0.0.0", 1313), io_service);

    udp_listener.start();

    io_service.run();
    /* code */
    return 0;
}
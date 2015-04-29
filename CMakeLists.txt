cmake_minimum_required(VERSION 3.0)

project(syslog-amqp CXX)

add_definitions(-g)
add_definitions(--std=c++1y)
add_definitions(-DASIO_STANDALONE)

include_directories(include)
include_directories(3rd_party/asio/asio/include)

add_subdirectory(src)

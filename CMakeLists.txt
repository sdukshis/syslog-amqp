cmake_minimum_required(VERSION 3.0)

project(syslog-amqp CXX)

add_definitions(-g)
add_definitions(--std=c++1y)

include_directories(include)

add_subdirectory(src)

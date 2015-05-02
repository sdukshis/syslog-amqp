cmake_minimum_required(VERSION 3.0)

project(syslog-amqp CXX)

add_definitions(-g)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Werror)
add_definitions(--std=c++1y)
add_definitions(-DASIO_STANDALONE)

include_directories(include)
include_directories(3rd_party/asio/asio/include)
include_directories(3rd_party/rapidjson/include)

add_subdirectory(src)

add_subdirectory(tests)


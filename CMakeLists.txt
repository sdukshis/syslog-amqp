cmake_minimum_required(VERSION 2.8)

project(syslog-amqp C CXX)

option(BUILD_TESTS "build unittests (default=ON)" ON)

add_definitions(-g)
add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Werror)
add_definitions(--std=c++14)
add_definitions(-DASIO_STANDALONE)

include_directories(include)
include_directories(3rd_party/asio/asio/include)
include_directories(3rd_party/rapidjson/include)

add_definitions(-w)
add_subdirectory(3rd_party/amqp-cpp)
remove_definitions(-w)

add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

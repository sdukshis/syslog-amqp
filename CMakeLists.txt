cmake_minimum_required(VERSION 2.8)

project(syslog-amqp C CXX)

add_definitions(-g)
add_definitions(-Wall)
add_definitions(-Wextra)
#add_definitions(-Werror)
# add_definitions(--std=c++1y)
add_definitions(--std=c++11)
#add_definitions(-faddress-sanitizer)
#add_definitions(-fno-omit-frame-pointer)
add_definitions(-DASIO_STANDALONE)

include_directories(include)
include_directories(3rd_party/asio/asio/include)
include_directories(3rd_party/rapidjson/include)

add_definitions(-Wno-unused-parameter)
add_definitions(-Wno-extra)
add_subdirectory(3rd_party/amqp-cpp)
remove_definitions(-Wno-extra)
remove_definitions(-Wno-unused-parameter)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)


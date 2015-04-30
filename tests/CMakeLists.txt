add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/gmock
                 ${CMAKE_CURRENT_BINARY_DIR}/gmock)

set(SOURCES
    test_DataObserver.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/include)
include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/gtest/include)

add_executable(syslog-amqp.test ${SOURCES})

target_link_libraries(syslog-amqp.test gtest_main gtest)

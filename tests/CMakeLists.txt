add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
add_definitions(-Wno-error)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/gmock
                 ${CMAKE_CURRENT_BINARY_DIR}/gmock)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/DataObservable.cpp
    ${CMAKE_SOURCE_DIR}/src/MessageId.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/include)
include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/gtest/include)

add_executable(syslog-amqp.test
    test_MessageId.cpp
    test_DataObserver.cpp
    ${SOURCES}
)

target_link_libraries(syslog-amqp.test gtest_main gtest gmock)

set(TEST_NAME syslog-amqp.test)

add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
add_definitions(-Wno-unused-local-typedefs)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/gmock
                 ${CMAKE_CURRENT_BINARY_DIR}/gmock)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/DataObservable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/MessageObservable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/MessageId.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Datetime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Message.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Endpoint.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/JsonMessageEncoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/IniParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Logging.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Options.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/gmock/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rd_party/gmock/gtest/include)

add_executable(${TEST_NAME}
    ${SOURCES}
    test_MessageId.cpp
    test_DataObserver.cpp
    test_Datetime.cpp
test_Message.cpp test_Endpoint.cpp test_JsonMessageEncoder.cpp test_MessageObserver.cpp test_IniParser.cpp test_Options.cpp)

target_link_libraries(${TEST_NAME}
    gtest_main
    gtest
    gmock
)

add_test(Unittests syslog-amqp.test)
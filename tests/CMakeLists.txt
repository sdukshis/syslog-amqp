add_definitions(-DGTEST_USE_OWN_TR1_TUPLE=1)
add_definitions(-Wno-error)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rd_party/gmock
                 ${CMAKE_CURRENT_BINARY_DIR}/gmock)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/DataObservable.cpp
    ${CMAKE_SOURCE_DIR}/src/MessageObservable.cpp
    ${CMAKE_SOURCE_DIR}/src/MessageId.cpp
    ${CMAKE_SOURCE_DIR}/src/Datetime.cpp
    ${CMAKE_SOURCE_DIR}/src/Message.cpp
    ${CMAKE_SOURCE_DIR}/src/Endpoint.cpp
    ${CMAKE_SOURCE_DIR}/src/JsonMessageEncoder.cpp

)

include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/include)
include_directories(${CMAKE_SOURCE_DIR}/3rd_party/gmock/gtest/include)

add_executable(syslog-amqp.test
    ${SOURCES}
    test_MessageId.cpp
    test_DataObserver.cpp
    test_Datetime.cpp
test_Message.cpp test_Endpoint.cpp test_JsonMessageEncoder.cpp test_MessageObserver.cpp)

target_link_libraries(syslog-amqp.test gtest_main gtest gmock)

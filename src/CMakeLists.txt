set(SOURCES
    UDPListener.cpp
    DataObservable.cpp
    MessageObservable.cpp
    Decoder.cpp
    Datetime.cpp
    Message.cpp
    MessageId.cpp
    Endpoint.cpp
)


add_executable(${PROJECT_NAME} main.cpp ${SOURCES} JsonMessageEncoder.cpp)

set(SOURCES
    UDPListener.cpp
    DataObservable.cpp
    MessageObservable.cpp
    Decoder.cpp
    Datetime.cpp
    Message.cpp
    MessageId.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

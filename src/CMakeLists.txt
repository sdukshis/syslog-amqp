find_package(Threads)

set(SOURCES
    UDPListener.cpp
    DataObservable.cpp
    MessageObservable.cpp
    Decoder.cpp
    Datetime.cpp
    Message.cpp
    MessageId.cpp
    Endpoint.cpp
    JsonMessageEncoder.cpp
    AsioRabbitMQPublisher.cpp
    PublishMessageObserver.cpp
)


add_executable(${PROJECT_NAME} main.cpp ${SOURCES} RabbitMQPublisherFactory.h AsioRabbitMQPublisherFactory.cpp AsioRabbitMQPublisherFactory.h AsioReactor.cpp AsioReactor.h StdoutPublisher.cpp StdoutPublisher.h)

target_link_libraries(${PROJECT_NAME}
    amqp-cpp
    ${CMAKE_THREAD_LIBS_INIT}
#    asan
)
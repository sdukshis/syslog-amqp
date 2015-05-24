//
// Created by Pavel Filonov on 24.05.15.
//

#include "ReactorBuilder.h"
#include "Options.h"
#include "UDPListener.h"
#include "AsioReactor.h"
#include "Decoder.h"
#include "JsonMessageEncoder.h"
#include "StdoutPublisher.h"
#include "PublishMessageObserver.h"
#include "RabbitMQPublisher.h"

void ReactorBuilder::buildFromOptions(AbstractReactor &reactor, const Options &options) {
    auto encoder = std::make_shared<JsonMessageEncoder>();
    auto decoder = std::make_shared<Decoder>();

    for (const auto &output : options.outputs) {
        switch (output.type) {
            case OutputOptins::Type::Stdout:
                decoder->addObserver(std::make_shared<StdoutPublisher>(encoder));
                break;
            case OutputOptins::Type::RabbitMQ:
                decoder->addObserver(
                        std::make_shared<PublishMessageObserver>(
                                *reactor.createRabbitMQPublisher(),
                                output.exchange,
                                RabbitMQPublisher::ExchangeType::Topic,
                                output.routing_key,
                                encoder));
                break;
        }
    }

    for (const auto &input : options.inputs) {
        switch (input.protocol) {
            case InputOptions::Protocol::UDP:
                reactor.createUDPListener(input.endpoint)->addObserver(decoder);
                break;
        }
    }
};

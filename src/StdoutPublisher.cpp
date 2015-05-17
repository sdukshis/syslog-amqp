//
// Created by Pavel Filonov on 17.05.15.
//

#include "StdoutPublisher.h"

#include <iostream>
#include <iterator>

#include "MessageEncoder.h"

StdoutPublisher::StdoutPublisher(MessageEncoder &encoder)
        : encoder_{encoder} {
}

void StdoutPublisher::onMessage(const Message &message) {
    encoder_.encode(message);
    std::cout.write(encoder_.begin(), encoder_.size());
    std::cout.flush();
}


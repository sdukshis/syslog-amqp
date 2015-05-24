//
// Created by Pavel Filonov on 17.05.15.
//

#include "StdoutPublisher.h"

#include <iostream>
#include <iterator>
#include <assert.h>

#include "MessageEncoder.h"

StdoutPublisher::StdoutPublisher(const std::shared_ptr<MessageEncoder> &encoder)
        : encoder_{encoder} {
    assert(encoder_);
}

void StdoutPublisher::onMessage(const Message &message) {
    encoder_->encode(message);
    std::cout.write(encoder_->begin(), encoder_->size());
    std::cout.flush();
}


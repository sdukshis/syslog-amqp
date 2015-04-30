#include "MessageId.h"

MessageId::MessageId() {}

std::string MessageId::toString() const {
    return "Id";    
}

void MessageId::toString(std::string &s) const {
    s = toString();
}

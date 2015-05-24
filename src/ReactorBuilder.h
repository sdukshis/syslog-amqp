//
// Created by Pavel Filonov on 24.05.15.
//

#ifndef SYSLOG_AMQP_REACTORBUILDER_H
#define SYSLOG_AMQP_REACTORBUILDER_H

#include "AbstractReactorBuilder.h"

class ReactorBuilder : public AbstractReactorBuilder {
public:
    void buildFromOptions(AbstractReactor &, const Options &options) override;
};


#endif //SYSLOG_AMQP_REACTORBUILDER_H

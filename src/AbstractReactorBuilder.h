//
// Created by Pavel Filonov on 24.05.15.
//

#ifndef SYSLOG_AMQP_ABSTRACTREACTORBUILDER_H
#define SYSLOG_AMQP_ABSTRACTREACTORBUILDER_H

class AbstractReactor;

struct Options;

class AbstractReactorBuilder {
public:
    virtual ~AbstractReactorBuilder() { }

    virtual void buildFromOptions(AbstractReactor &, const Options &options) = 0;
};

#endif //SYSLOG_AMQP_ABSTRACTREACTORBUILDER_H

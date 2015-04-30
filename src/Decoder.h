#ifndef DECODER_H
#define DECODER_H

#include <string>

#include "DataObserver.h"
#include "MessageObservable.h"

class Decoder: public DataObserver, public MessageObservable {
 public:
    Decoder();

    Decoder(const Decoder &) = delete;

    Decoder(Decoder &&);

    ~Decoder() override { }

    Decoder & operator=(const Decoder &) = delete;

    Decoder & operator=(Decoder &&);

    void onBegin(const Endpoint &recv_host, const std::string &tag) override;

    void onData(const char *buffer, std::size_t length) override;

    void onEnd() override;

 private:
    std::string recv_buffer_;
    Endpoint recv_host_;
    std::string tag_;
};  // class Decoder

#endif  // DECODER_H

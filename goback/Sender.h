#ifndef GBN_SENDER_H
#define GBN_SENDER_H
#include "../simu/DataStructure.h"
#include "../simu/RdtSender.h"
#include "../util/util.h"
#include <list>

class GBNSender: public RdtSender, public AbstractEntity {
    private:
    int seq;
    const int wndsz;
    std::list<Packet> window;
    bool wait();
    public:
    GBNSender(int windowsz);
    virtual ~GBNSender();
    bool getWaitingState();
    bool send(Message& msg);
    void receive(Packet& pkt);
    void timeoutHandler(int seq);
};


#endif
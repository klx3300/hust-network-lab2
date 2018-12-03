#ifndef STCP_SENDER_H
#define STCP_SENDER_H
#include "../simu/DataStructure.h"
#include "../simu/RdtSender.h"
#include "../util/util.h"
#include <list>

class STCPSender: public RdtSender, public AbstractEntity {
    private:
    int seq;
    int rack_counter;
    const int wndsz;
    std::list<Packet> window;
    bool wait();
    public:
    STCPSender(int windowsz);
    virtual ~STCPSender();
    bool getWaitingState();
    bool send(Message& msg);
    void receive(Packet& pkt);
    void timeoutHandler(int seq);
};


#endif
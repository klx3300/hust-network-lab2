#ifndef SR_SENDER_H
#define SR_SENDER_H
#include "../simu/DataStructure.h"
#include "../simu/RdtSender.h"
#include "../util/util.h"
#include <list>
#include <utility>

class SRSender: public RdtSender, public AbstractEntity {
    private:
    int seq;
    const int wndsz;
    std::list<std::pair<Packet, bool>> window;
    bool wait();
    public:
    SRSender(int windowsz);
    virtual ~SRSender();
    bool getWaitingState();
    bool send(Message& msg);
    void receive(Packet& pkt);
    void timeoutHandler(int seq);
};


#endif
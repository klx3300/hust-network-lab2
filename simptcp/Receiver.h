#ifndef STCP_RECV_H
#define STCP_RECV_H
#include "../simu/DataStructure.h"
#include "../simu/RdtReceiver.h"
#include "../util/util.h"
#include <list>

class STCPReceiver: public RdtReceiver, public AbstractEntity {
    private:
    int seq;
    void onRecv(Packet& pkt);
    public:
    STCPReceiver();
    virtual ~STCPReceiver();
    virtual void receive(Packet& pkt){onRecv(pkt);};
};

#endif
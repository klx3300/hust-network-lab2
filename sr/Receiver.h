#ifndef SR_RECV_H
#define GBN_RECV_H
#include "../simu/DataStructure.h"
#include "../simu/RdtReceiver.h"
#include "../util/util.h"
#include "../util/pktbuffer.h"
#include <list>

class SRReceiver: public RdtReceiver, public AbstractEntity {
    private:
    PacketBuffer pb;
    void onRecv(Packet& pkt);
    public:
    SRReceiver(int wndsz);
    virtual ~SRReceiver();
    virtual void receive(Packet& pkt){onRecv(pkt);};
};

#endif
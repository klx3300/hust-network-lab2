#ifndef GBN_RECV_H
#define GBN_RECV_H
#include "../simu/DataStructure.h"
#include "../simu/RdtReceiver.h"
#include "../util/util.h"
#include <list>

class GBNReceiver: public RdtReceiver, public AbstractEntity {
    private:
    int seq;
    void onRecv(Packet& pkt);
    public:
    GBNReceiver();
    virtual ~GBNReceiver();
    virtual void receive(Packet& pkt){onRecv(pkt);};
};

#endif
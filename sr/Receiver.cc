#include "Receiver.h"
#include "../format/log.h"
#include "../simu/Global.h"
#include "../util/util.h"
#include "../simu/RandomEventEnum.h"
using namespace std;
SRReceiver::SRReceiver(int wndsz):AbstractEntity(RECEIVER), pb(wndsz){}

SRReceiver::~SRReceiver(){}

void SRReceiver::onRecv(Packet& pkt){
    if(checksum(pkt) != pkt.checksum){
        qLogWarnfmt("SRReceiver: packet checksum mismatch: expect %d, got %d",
        pkt.checksum, checksum(pkt));
        // IGNORE IT
        return;
    }
    // try put it into the pktbuffer
    if(!pb.accept(pkt)){
        qLogWarnfmt("SRReceiver: window overflow: %d, ignored", pkt.seqnum);
        return;
    }
    // successfully put into pktbuffer
    // generate ack for it
    qLogWarnfmt("SRReceiver: generating ack for %d", pkt.seqnum);
    *this << mkack(pkt.seqnum);
    Packet nxpkt;
    while(pb.generator(nxpkt)){
        qLogWarnfmt("SRReceiver: generating redundant ack for moved window %d", pkt.seqnum);
        // generate some redundant ACKs to accelerate sender process
        *this << mkack(nxpkt.seqnum);
        deliver(nxpkt);
    }
    return;
}
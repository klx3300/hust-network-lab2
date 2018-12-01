#include "Receiver.h"
#include "../format/log.h"
#include "../simu/Global.h"
#include "../util/util.h"
#include "../simu/RandomEventEnum.h"
using namespace std;
GBNReceiver::GBNReceiver():seq(0), AbstractEntity(RECEIVER){}

GBNReceiver::~GBNReceiver(){}

void GBNReceiver::onRecv(Packet& pkt){
    if(checksum(pkt) != pkt.checksum){
        // checksum mismatch, resend ACK as NAK
        qLogWarnfmt("GBNReceiver: packet checksum mismatch: expect %d, got %d",
        pkt.checksum, checksum(pkt));
        *this << mkack(seq);
        return;
    }
    if(pkt.seqnum != seq + 1){
        // misordered packet, resend ACK as NAK
        qLogWarnfmt("GBNReceiver: packet sequence mismatch: expect %d, got %d",
        seq + 1, pkt.seqnum);
        *this << mkack(seq);
        return;
    }
    // CHECK PASSED
    qLogSuccfmt("GBNReceiver: packet %s delivered.", ((string)Dumper(pkt, DUMP_STRING)).c_str());
    seq ++;
    deliver(pkt);
    *this << mkack(seq);
}
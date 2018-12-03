#include "pktbuffer.h"
#include "../format/log.h"

using namespace std;

PacketBuffer::PacketBuffer(int mr):
maxsize(mr), currmin(0){}

bool PacketBuffer::exist(int pktseq){
    return buf.find(pktseq) != buf.end();
}

bool PacketBuffer::redundant(int pktseq){
    return rsmaller(pktseq, currmin);
}

bool PacketBuffer::accept(const Packet& pkt){
    if(currmin == 0) currmin = 1;
    if((pkt.seqnum - currmin >= maxsize)) {
        return false;
    }
    if(redundant(pkt.seqnum)){
        return true;
    }
    qLogInfofmt("PacketBuffer: accepted %d", pkt.seqnum);
    buf[pkt.seqnum] = pkt;
    return true;
}

bool PacketBuffer::generator(Packet& pkt){
    if(exist(currmin)){
        pkt = buf[currmin];
        buf.erase(buf.find(currmin));
        currmin++;
        return true;
    }
    qLogInfofmt("PacketBuffer: currmin %d not exist yet.", currmin);
    return false;
}

bool PacketBuffer::get(int seqnum, Packet& pkt){
    if(!exist(seqnum)) return false;
    pkt = buf[seqnum];
    return true;
}

void PacketBuffer::exhaust(int seqnum){
    if(!exist(seqnum)) return;
    buf.erase(buf.find(seqnum));
}


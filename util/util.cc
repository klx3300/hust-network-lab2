#include "util.h"
#include "../simu/Global.h"
#include <cstring>
#include <cstdio>

using namespace std;

int checksum(Packet& pkt){
    return pUtils->calculateCheckSum(pkt);
}

void timer_(RandomEventTarget identity, int id, int timeout){
    pns->startTimer(identity, timeout, id);
}
void stoptimer_(RandomEventTarget identity, int id){
    pns->stopTimer(identity, id);
}

bool rsmaller(int a, int b){
    return (a - b) < 0;
}

Message mkmsg(const Packet& pkt){
    Message msg;
    memcpy(msg.data, pkt.payload, sizeof(pkt.payload));
    return msg;
}

Packet mkack(int seq){
    Packet pkt;
    pkt.acknum = seq;
    pkt.checksum = checksum(pkt);
    return pkt;
}

Packet mkdat(const Message& msg, int seq){
    Packet pkt;
    memcpy(pkt.payload, msg.data, sizeof(msg.data));
    pkt.seqnum = seq;
    pkt.checksum = checksum(pkt);
    return pkt;
}

AbstractEntity::AbstractEntity(RandomEventTarget eid): myself(eid),
    other(eid == SENDER ? RECEIVER : SENDER){}

void AbstractEntity::timer(int timerid, int timeout){
    timer_(myself, timerid, timeout);
}

void AbstractEntity::stoptimer(int timerid){
    stoptimer_(myself, timerid);
}

void AbstractEntity::operator<<(const Packet& pkt){
        pns->sendToNetworkLayer(other, pkt);
}

void AbstractEntity::deliver(const Packet& pkt){
    pns->delivertoAppLayer(myself, mkmsg(pkt));
}

Dumper::Dumper(const Packet& pkt, DumpMode mod):
mode(mod), data(pkt.payload), size(sizeof(pkt.payload)){}

Dumper::Dumper(const Message& pkt, DumpMode mod):
mode(mod), data(pkt.data), size(sizeof(pkt.data)){}

Dumper::operator string(){
    if(mode == DUMP_STRING){
        return ("[" + string(data)) + "]";
    } else {
        string tmp = "[";
        char tmpcharr[40] = {0};
        for(int i = 0; i < size; i++){
            sprintf(tmpcharr, "%hhu", data[i]);
            tmp += tmpcharr;
            if(i != size - 1){
                tmp += ", ";
            } else {
                tmp += "]";
            }
        }
        return tmp;
    }
}
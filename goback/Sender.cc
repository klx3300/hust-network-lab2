#include "Sender.h"
#include "../format/log.h"
#include "../simu/Global.h"
#include "../util/util.h"
#include "../simu/RandomEventEnum.h"
using namespace std;

GBNSender::GBNSender(int windowSz):
wndsz(windowSz), seq(0), AbstractEntity(SENDER){
    qLogSuccfmt("GBNSender: Initialization %d", windowSz);
}

GBNSender::~GBNSender(){}

bool GBNSender::wait(){
    return window.size() >= wndsz;
}

bool GBNSender::getWaitingState(){
    return wait();
}

bool GBNSender::send(Message& msg){
    if(wait()) return false;
    seq++;
    qLogInfofmt("GBNSender: Application Issued %d %s", seq, 
    ((string)Dumper(msg, DUMP_STRING)).c_str());
    Packet pkt = mkdat(msg, seq);
    window.push_back(pkt);
    *this << pkt;
    stoptimer(0);
    timer(0, Configuration::TIME_OUT);
    return true;
}

void GBNSender::receive(Packet& pkt){
    // check checksum
    if(checksum(pkt) != pkt.checksum){
        qLogWarnfmt("GBNSender: packet checksum mismatch: expect %d, got %d",
        pkt.checksum, checksum(pkt));
        return;
    }
    // check if it's redundant ACK
    if(rsmaller(pkt.acknum ,window.begin()->seqnum)){
        qLogWarnfmt("GBNSender: redundant ACK found, HEAD %d, ACK %d",
        window.begin()->seqnum, pkt.acknum);
        // arrange resend
        for(auto &x: window){
            *this << x;
        }
        return;
    }
    // then it's not redundant
    while((window.size() != 0) &&
        (rsmaller(window.begin()->seqnum, pkt.acknum) || window.begin()->seqnum == pkt.acknum)){
        qLogSuccfmt("GBNSender: Acknowleged %d", window.begin()->seqnum);
        window.pop_front();
    }
    qLogInfo("GBNSender: Acknowlegement complete.");
}

void GBNSender::timeoutHandler(int id){
    // we only setup one timeout handler..
    qLogWarn("GBNSender: timed out.");
    for(auto &x: window){
        *this << x;
    }
    if(window.size() != 0){
        timer(0, Configuration::TIME_OUT);
    }
}

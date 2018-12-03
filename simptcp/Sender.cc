#include "Sender.h"
#include "../format/log.h"
#include "../simu/Global.h"
#include "../util/util.h"
#include "../simu/RandomEventEnum.h"
using namespace std;

STCPSender::STCPSender(int windowSz):
wndsz(windowSz), seq(0), rack_counter(0), AbstractEntity(SENDER){
    qLogSuccfmt("STCPSender: Initialization %d", windowSz);
}

STCPSender::~STCPSender(){}

bool STCPSender::wait(){
    return window.size() >= wndsz;
}

bool STCPSender::getWaitingState(){
    return wait();
}

bool STCPSender::send(Message& msg){
    if(wait()) return false;
    seq++;
    qLogInfofmt("STCPSender: Application Issued %d %s", seq, 
    ((string)Dumper(msg, DUMP_STRING)).c_str());
    Packet pkt = mkdat(msg, seq);
    window.push_back(pkt);
    *this << pkt;
    stoptimer(0);
    timer(0, Configuration::TIME_OUT);
    return true;
}

void STCPSender::receive(Packet& pkt){
    // check checksum
    if(checksum(pkt) != pkt.checksum){
        qLogWarnfmt("STCPSender: packet checksum mismatch: expect %d, got %d",
        pkt.checksum, checksum(pkt));
        return;
    }
    // check if it's redundant ACK
    if(rsmaller(pkt.acknum ,window.begin()->seqnum)){
        qLogWarnfmt("STCPSender: redundant ACK found, HEAD %d, ACK %d",
        window.begin()->seqnum, pkt.acknum);
        rack_counter++;
        if(rack_counter == 3){
            rack_counter = 0;
            stoptimer(0);
            timer(0, Configuration::TIME_OUT);
            if(window.size() != 0){
                qLogWarnfmt("STCPSender: fast retransmit triggered, retransmit %d", window.begin()->seqnum);
                *this << *window.begin();
            }
        }
    }
    // then it's not redundant
    rack_counter = 0;
    while((window.size() != 0) &&
        (rsmaller(window.begin()->seqnum, pkt.acknum) || window.begin()->seqnum == pkt.acknum)){
        qLogSuccfmt("STCPSender: Acknowleged %d", window.begin()->seqnum);
        window.pop_front();
    }
    qLogInfo("STCPSender: Acknowlegement complete.");
}

void STCPSender::timeoutHandler(int id){
    // we only setup one timeout handler..
    qLogWarn("STCPSender: timed out.");
    if(window.size() != 0){
        qLogInfofmt("STCPSender: retransmitting %d", window.begin()->seqnum);
        *this << *window.begin();
    }
    if(window.size() != 0){
        timer(0, Configuration::TIME_OUT);
    }
}

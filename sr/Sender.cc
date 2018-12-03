#include "Sender.h"
#include "../format/log.h"
#include "../simu/Global.h"
#include "../util/util.h"
#include "../simu/RandomEventEnum.h"
using namespace std;

SRSender::SRSender(int windowSz):
wndsz(windowSz), seq(0), AbstractEntity(SENDER){
    qLogSuccfmt("SRSender: Initialization %d", windowSz);
}

SRSender::~SRSender(){}

bool SRSender::wait(){
    return window.size() >= wndsz;
}

bool SRSender::getWaitingState(){
    return wait();
}

bool SRSender::send(Message& msg){
    if(wait()) return false;
    seq++;
    qLogInfofmt("SRSender: Application Issued %d %s", seq, 
    ((string)Dumper(msg, DUMP_STRING)).c_str());
    Packet pkt = mkdat(msg, seq);
    window.push_back(pair<Packet, bool>(pkt, false));
    *this << pkt;
    timer(seq, Configuration::TIME_OUT);
    return true;
}

void SRSender::receive(Packet& pkt){
    // check checksum
    if(checksum(pkt) != pkt.checksum){
        qLogWarnfmt("SRSender: packet checksum mismatch: expect %d, got %d",
        pkt.checksum, checksum(pkt));
        return;
    }
    // check if it's redundant ACK
    if(rsmaller(pkt.acknum, window.begin()->first.seqnum)){
        qLogWarnfmt("SRSender: redundant ACK found, HEAD %d, ACK %d",
        window.begin()->first.seqnum, pkt.acknum);
        return;
    }
    // then it's not redundant
    // first, we try to mark it ACKed
    for(auto &x: window){
        if(x.first.seqnum == pkt.acknum){
            x.second = true;
            stoptimer(pkt.acknum);
            break;
        }
    }
    // second, we try to move the window..
    while((window.size() != 0) && (window.begin()->second == true)){
        qLogSuccfmt("SRSender: Acknowleged %d", window.begin()->first.seqnum);
        window.pop_front();
    }
    qLogInfo("SRSender: Acknowlegement complete.");
}

void SRSender::timeoutHandler(int id){
    qLogWarnfmt("SRSender: timed out for %d.", id);
    for(auto &x: window){
        if(x.first.seqnum == id && x.second == false){
            *this << x.first;
            timer(id, Configuration::TIME_OUT);
            return;
        }
    }
}

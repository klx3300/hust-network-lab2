#ifndef UTILS_PKTBUFFER_H
#define UTILS_PKTBUFFER_H
#include "../simu/DataStructure.h"
#include <map>
#include "util.h"

class PacketBuffer {
    private:
    std::map<int, Packet> buf;
    const int maxsize;
    int currmin;
    public:
    PacketBuffer(int mxrange);
    // false: this pkt not in buffer
    // true: this pkt already in buffer
    bool exist(int pktseq);
    // false: failed
    // true: this time succeed
    bool accept(const Packet& pkt);
    // false: no avail left
    // true: may continue extract
    bool generator(Packet& pktn);
    bool redundant(int pktseq);
    bool get(int seqnum, Packet& pkt);
    void exhaust(int seqnum);
};

#endif
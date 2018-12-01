#ifndef UTIL_H
#define UTIL_H
#include "../simu/Tool.h"
#include "../simu/DataStructure.h"
#include "../simu/RandomEventEnum.h"
#include <string>

int checksum(Packet& pkt);
void timer_(RandomEventTarget identity, int id, int timeout);
void stoptimer_(RandomEventTarget identity, int id);
Message mkmsg(const Packet& pkt);
Packet mkack(int seq);
Packet mkdat(const Message& msg, int seq);

bool rsmaller(int a, int b);

struct AbstractEntity{
    public:
    AbstractEntity(RandomEventTarget eid);
    void timer(int timerid, int timeout);
    void stoptimer(int timerid);
    void operator<<(const Packet& pkt);
    void deliver(const Packet& pkt);
    private:
    const RandomEventTarget myself;
    const RandomEventTarget other;
};

enum DumpMode {
    DUMP_STRING = 0,
    DUMP_BINARY
};

struct Dumper{
    public:
    Dumper(const Packet& pkt, DumpMode mod);
    Dumper(const Message& msg, DumpMode mod);
    operator std::string();
    private:
    const DumpMode mode;
    const char* data;
    int size;
};

#endif
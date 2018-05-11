/* Kamil Breczko (280 990) */

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <vector>
#include <set>
#include <stdexcept>
#include <memory>
#include <unistd.h>

#include "Sender.h"
#include "Receiver.h"

#define MAX_TTL 30
#define MAX_PACKET_PER_TTL 3
#define WAITING_TIME 1

using namespace std;

typedef chrono::high_resolution_clock::time_point time_point;

class Traceroute {
private:
    u_int16_t pid;
    int sockfd;
public:
    Traceroute(u_int16_t pid);

    ~Traceroute();

    void run(const char *ipAddress);

    void printRoute(u_int16_t ttl, vector<Packet> receivedPackets, time_point sendingTime);
};

#endif

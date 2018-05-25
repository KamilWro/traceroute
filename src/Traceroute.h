/* Kamil Breczko (280 990) */

#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <vector>
#include <set>
#include <stdexcept>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include "Sender.h"
#include "Receiver.h"
#include "Sockwrap.h"

#define MAX_TTL 30
#define MAX_PACKET_PER_TTL 3
#define WAITING_TIME_S 1
#define WAITING_TIME_US 0

using namespace std;

typedef chrono::high_resolution_clock::time_point time_point;

class Traceroute {
private:
    uint16_t pid;
    int sockfd;
public:
    Traceroute(uint16_t pid);

    ~Traceroute();

    void run(const char *ipAddress);

    void printRoute(uint16_t ttl, vector<Packet> receivedPackets, time_point sendingTime);
};

#endif

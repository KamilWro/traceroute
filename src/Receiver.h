/* Kamil Breczko (280 990) */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>

#include "Packet.h"
#include "Sockwrap.h"

class Receiver {
    struct icmp *getMyIcmpHeader(u_int8_t *icmpPacket) const;

    Packet extractICMP(uint8_t *buffer, char *address, time_point receiptTime);

public:

    Packet receivePacket(int sockfd);
};

#endif

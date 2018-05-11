/* Kamil Breczko (280 990) */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>

#include "Packet.h"

class Receiver {
    struct icmp *getSentIcmpHeader(u_int8_t *icmp_packet) const;

public:
    struct Packet receivePacket(int sockfd);
};

#endif

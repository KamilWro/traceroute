/* Kamil Breczko (280 990) */

#ifndef SENDER_H
#define SENDER_H

#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

#include "Sockwrap.h"

class Sender {
    struct sockaddr_in recipient;
    uint16_t pid;

    uint16_t computeIcmpChecksum(const void *buff, int length);

    struct icmphdr createIcmpHeader(uint16_t sequence);

public:
    Sender(const char *ipAddress, uint16_t pid);

    void sendPacket(int sockfd, int ttl, uint16_t sequence);

};


#endif

/* Kamil Breczko (280 990) */

#ifndef SENDER_H
#define SENDER_H

#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

class Sender {
    struct sockaddr_in recipient;
    uint16_t pid;

    u_int16_t computeIcmpChecksum(const void *buff, int length);

    struct icmphdr createIcmpHeader(u_int16_t sequence);

public:
    Sender(const char *ipAddress, u_int16_t pid);

    void sendPacket(int sockfd, int ttl, u_int16_t sequence);

};


#endif

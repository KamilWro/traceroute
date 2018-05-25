/* Kamil Breczko (280 990) */

#include "Receiver.h"

Packet Receiver::receivePacket(int sockfd) {
    struct sockaddr_in sender{};
    socklen_t senderLen = sizeof(sender);
    uint8_t buffer[IP_MAXPACKET + 1];

    RecvFrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr *) &sender, &senderLen);
    auto receiptTime = chrono::high_resolution_clock::now();

    char senderIpAddress[INET_ADDRSTRLEN];
    Inet_ntop(AF_INET, &(sender.sin_addr), senderIpAddress, sizeof(senderIpAddress));

    return extractICMP(buffer, senderIpAddress, receiptTime);
}

Packet Receiver::extractICMP(uint8_t *buffer, char *address, time_point receiptTime) {
    auto *ipHeader = (struct iphdr *) buffer;
    uint8_t *icmpPacket = buffer + 4 * ipHeader->ihl;
    auto *icmpHeader = (struct icmphdr *) icmpPacket;

    uint16_t sequence = 0;
    uint16_t id = 0;

    if (icmpHeader->type == ICMP_ECHOREPLY) {
        sequence = icmpHeader->un.echo.sequence;
        id = icmpHeader->un.echo.id;
    }

    if (icmpHeader->type == ICMP_TIME_EXCEEDED) {
        icmp *myIcmpHeader = getMyIcmpHeader(icmpPacket);
        sequence = myIcmpHeader->icmp_seq;
        id = myIcmpHeader->icmp_id;
    }

    return Packet(id, sequence, address, receiptTime);
}

struct icmp *Receiver::getMyIcmpHeader(uint8_t *icmpPacket) const {
    uint8_t *myIpPacket = icmpPacket + 8;
    auto *myIpHeader = (struct ip *) myIpPacket;
    uint8_t *myIcmpPacket = myIpPacket + myIpHeader->ip_hl * 4;
    auto *myIcmpHeader = (struct icmp *) myIcmpPacket;
    return myIcmpHeader;
}

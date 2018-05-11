/* Kamil Breczko (280 990) */

#include "Receiver.h"

struct Packet Receiver::receivePacket(int sockfd) {
    struct sockaddr_in sender{};
    socklen_t senderLen = sizeof(sender);
    u_int8_t buffer[IP_MAXPACKET + 1];

    /* otrzymany pakiet z gniazda kopiowany jest do bufora */
    ssize_t packetSize = recvfrom(sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr *) &sender, &senderLen);
    auto receiptTime = std::chrono::high_resolution_clock::now();
    if (packetSize < 0)
        throw std::runtime_error(std::string("recvfrom error: ") + strerror(errno));

    char senderIpAddress[INET_ADDRSTRLEN];
    const char *dst = inet_ntop(AF_INET, &(sender.sin_addr), senderIpAddress, sizeof(senderIpAddress));
    if (dst == nullptr)
        throw std::runtime_error(std::string("inet_ntop error: ") + strerror(errno));

    auto *ipHeader = (struct iphdr *) buffer;
    u_int8_t *icmpPacket = buffer + 4 * ipHeader->ihl;
    auto *icmpHeader = (struct icmphdr *) icmpPacket;

    u_int16_t sequence = 0;
    u_int16_t id = 0;

    /* komunikat osiagnal swoje przeznaczenie */
    if (icmpHeader->type == ICMP_ECHOREPLY) {
        sequence = icmpHeader->un.echo.sequence;
        id = icmpHeader->un.echo.id;
    }

    /* pole TTL osiagnelo wartosc 0 */
    if (icmpHeader->type == ICMP_TIME_EXCEEDED) {
        icmp *myIcmpHeader = getMyIcmpHeader(icmpPacket);

        sequence = myIcmpHeader->icmp_seq;
        id = myIcmpHeader->icmp_id;
    }

    return Packet(id, sequence, senderIpAddress, receiptTime);
}

/* wyciagniecie wyslanego przez nas pakietu z naglowka ICMP */
struct icmp *Receiver::getMyIcmpHeader(u_int8_t *icmpPacket) const {
    u_int8_t *myIpPacket = icmpPacket + 8;
    auto *myIpHeader = (struct ip *) myIpPacket;
    u_int8_t *myIcmpPacket = myIpPacket + myIpHeader->ip_hl * 4;
    auto *myIcmpHeader = (struct icmp *) myIcmpPacket;
    return myIcmpHeader;
}

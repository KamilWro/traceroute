/* Kamil Breczko (280 990) */

#include "Sender.h"

void Sender::sendPacket(int sockfd, int ttl, uint16_t sequence) {
    struct icmphdr icmphdr = createIcmpHeader(sequence);
    Setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    SendTo(sockfd, &icmphdr, sizeof(icmphdr), 0, (struct sockaddr *) &recipient, sizeof(recipient));
}

struct icmphdr Sender::createIcmpHeader(uint16_t sequence) {
    struct icmphdr icmpHeader{};
    icmpHeader.type = ICMP_ECHO;
    icmpHeader.code = 0;
    icmpHeader.un.echo.id = pid;
    icmpHeader.un.echo.sequence = sequence;
    icmpHeader.checksum = 0;
    icmpHeader.checksum = computeIcmpChecksum((uint16_t *) &icmpHeader, sizeof(icmpHeader));
    return icmpHeader;
}

u_int16_t Sender::computeIcmpChecksum(const void *buff, int length) {
    if (length % 2 != 0)
        throw std::invalid_argument("checksum error: size of struct % 2 != 0");

    u_int32_t sum;
    const auto *ptr = static_cast<const uint16_t *>(buff);

    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t) (~(sum + (sum >> 16)));
}

Sender::Sender(const char *ipAddress, uint16_t pid) : pid(pid) {
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    Inet_pton(AF_INET, ipAddress, &recipient.sin_addr);
}

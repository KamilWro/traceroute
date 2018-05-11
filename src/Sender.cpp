/* Kamil Breczko (280 990) */

#include "Sender.h"

void Sender::sendPacket(int sockfd, int ttl, u_int16_t sequence) {
    struct icmphdr icmphdr = createIcmpHeader(sequence);

    int result = setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    if (result < 0)
        throw std::invalid_argument(std::string("setsockopt error: ") + strerror(errno));

    ssize_t bytesSent = sendto(sockfd, &icmphdr, sizeof(icmphdr), 0, (struct sockaddr *) &recipient, sizeof(recipient));
    if (bytesSent <= 0)
        throw std::runtime_error("sento error: Packet was not sent");
}

struct icmphdr Sender::createIcmpHeader(u_int16_t sequence) {
    struct icmphdr icmpHeader{};
    icmpHeader.type = ICMP_ECHO;
    icmpHeader.code = 0;
    icmpHeader.un.echo.id = pid;
    icmpHeader.un.echo.sequence = sequence;
    icmpHeader.checksum = 0;
    icmpHeader.checksum = computeIcmpChecksum((u_int16_t *) &icmpHeader, sizeof(icmpHeader));
    return icmpHeader;
}

u_int16_t Sender::computeIcmpChecksum(const void *buff, int length) {
    if (length % 2 != 0)
        throw std::invalid_argument("checksum error: size of struct % 2 != 0");

    u_int32_t sum;
    const auto *ptr = static_cast<const u_int16_t *>(buff);

    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t) (~(sum + (sum >> 16)));
}

Sender::Sender(const char *ipAddress, u_int16_t pid) : pid(pid) {
    // Wpisujemy adres odbiorcy do struktury adresowej
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    int address = inet_pton(AF_INET, ipAddress, &recipient.sin_addr);

    if (address == 0)
        throw std::invalid_argument("error: incorrect IPv4 address");

    if (address == -1)
        throw std::invalid_argument(std::string("inet_pton error:") + strerror(errno));
}

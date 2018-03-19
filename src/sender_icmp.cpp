/* Kamil Breczko (280 990) */

#include "sender_icmp.h"

void Sender_icmp::send_packet(int ttl, u_int16_t sequence) {
    struct icmphdr icmphdr = create_icmphdr(sequence);
    struct sockaddr_in recipient;

    // Wpisujemy adres odbiorcy do struktury adresowej
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    int is_address = inet_pton(AF_INET, ip_addr, &recipient.sin_addr);

    if (is_address == 0)
        throw std::invalid_argument("error: incorrect IPv4 address");

    if (is_address == -1)
        throw std::invalid_argument(std::string("inet_pton error:") + strerror(errno));

    int set_ttl = setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    if (set_ttl < 0)
        throw std::invalid_argument(std::string("setsockopt error: ") + strerror(errno));

    ssize_t bytes_sent = sendto(sockfd, &icmphdr, sizeof(icmphdr), 0, (struct sockaddr *) &recipient,
                                sizeof(recipient));
    if (bytes_sent <= 0)
        throw std::runtime_error("sento error: packet was not sent");
}

struct icmphdr Sender_icmp::create_icmphdr(u_int16_t sequence) {
    struct icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = pid;
    icmp_header.un.echo.sequence = sequence;
    icmp_header.checksum = 0;
    icmp_header.checksum = compute_icmp_checksum((u_int16_t *) &icmp_header, sizeof(icmp_header));
    return icmp_header;
}

u_int16_t Sender_icmp::compute_icmp_checksum(const void *buff, int length) {
    if (length % 2 != 0)
        throw std::invalid_argument("checksum error: size of struct % 2 != 0");

    u_int32_t sum;
    const u_int16_t *ptr = static_cast<const u_int16_t *>(buff);

    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t) (~(sum + (sum >> 16)));
}

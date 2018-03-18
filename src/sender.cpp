/*
 * Kamil Breczko
 * nr. indeksu: 280990
 */
#include <netinet/ip_icmp.h>
#include "sender.h"

Sender::Sender(u_int16_t pid, const char *ip_addr, int sockfd) : pid(pid), ip_addr(ip_addr), sockfd(sockfd) {}

void Sender::send_packet(int ttl, u_int16_t sequence) {
    struct icmphdr icmphdr = create_icmphdr(sequence);
    struct sockaddr_in recipient;

    // Wpisujemy adres odbiorcy do struktury adresowej
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    inet_pton(AF_INET, ip_addr, &recipient.sin_addr);

    setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
    ssize_t bytes_sent = sendto(sockfd, &icmphdr, sizeof(icmphdr), 0, (struct sockaddr *) &recipient,
                                sizeof(recipient));
    assert(bytes_sent > 0);
}

struct icmphdr Sender::create_icmphdr(u_int16_t sequence) {
    struct icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = pid;
    icmp_header.un.echo.sequence = sequence;
    icmp_header.checksum = 0;
    icmp_header.checksum = compute_icmp_checksum((u_int16_t *) &icmp_header, sizeof(icmp_header));
    return icmp_header;
}

u_int16_t Sender::compute_icmp_checksum(const void *buff, int length) {
    u_int32_t sum;
    const u_int16_t *ptr = static_cast<const u_int16_t *>(buff);
    assert (length % 2 == 0);

    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t) (~(sum + (sum >> 16)));
}

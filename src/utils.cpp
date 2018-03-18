/*
 * Kamil Breczko
 * nr. indeksu: 280 990
 */

#include "utils.h"

void print_route(u_int16_t ttl, std::vector<Packet> received_packets, time_point sending_time) {
    printf("%*d. \t", 2, ttl);

    if (received_packets.size() == 0) {
        printf("* \n");
        return;
    }

    std::set<const char *> ip_addresses;

    for (auto packet: received_packets)
        ip_addresses.insert(packet.ip_address);

    for (auto ip_address : ip_addresses)
        printf("%*s ", 15, ip_address);

    if (received_packets.size() != MAX_PACKET_PER_TTL) {
        printf("??? \n");
        return;
    }

    u_int32_t sum_time = 0;
    for (auto packet : received_packets) {
        sum_time += std::chrono::duration_cast<std::chrono::milliseconds>(
                packet.receipt_time - sending_time).count();
    }

    printf("%ums \n", sum_time / 3);
}

bool is_valid_args(int argc, const char **argv) {
    if (argc < 1 || argc > 2) {
        fprintf(stderr, "incorrect number of arguments \n");
        return false;
    }

    struct sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;

    int is_address = inet_pton(AF_INET, argv[1], &recipient.sin_addr);

    if (is_address == 0) {
        fprintf(stderr, "incorrect IPv4 address \n");
        return false;
    }

    if (is_address == -1) {
        fprintf(stderr, "inet_pton error: %s \n", strerror(errno));
        return false;
    }

    return true;
}
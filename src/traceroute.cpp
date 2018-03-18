/*
 * Kamil Breczko
 * nr. indeksu: 280 990
 */


#include "utils.h"
#include "sender.h"
#include "receiver.h"

int main(int argc, const char *argv[]) {
    if (!is_valid_args(argc, argv)) {
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return -1;
    }

    int pid = getpid();
    u_int16_t sequence = 0;
    bool destination = false;

    std::vector<struct Packet> received_packets;
    Sender sender(pid, argv[1], sockfd);
    Receiver receiver(sockfd);

    for (int ttl = 1; ttl <= MAX_TTL && !destination; ttl++) {

        for (int i = 0; i < MAX_PACKET_PER_TTL; i++)
            sender.send_packet(ttl, sequence++);

        time_point sending_time = std::chrono::high_resolution_clock::now();

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        while (received_packets.size() < MAX_PACKET_PER_TTL) {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);

            if (ready < 0) {
                fprintf(stderr, "waiting for the package in the socket has failed");
                return -1;
            } else if (ready == 0)
                break;

            Packet packet = receiver.receive_packet();
            if (packet.id == pid && (packet.sequence / MAX_PACKET_PER_TTL + 1) == ttl &&
                strcmp(packet.ip_address, "")) {
                received_packets.push_back(packet);
                if (!strcmp(packet.ip_address, argv[1]))
                    destination = true;
            }
        }

        print_route(ttl, received_packets, sending_time);
        received_packets.clear();
    }

    return 0;
}
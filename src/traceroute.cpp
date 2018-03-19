/* Kamil Breczko (280 990) */

#include "traceroute.h"

Traceroute::Traceroute(int pid) : pid(pid) {
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0)
        throw runtime_error(string("socket error: ") + strerror(errno));
}

void Traceroute::run(const char *ip_address, shared_ptr<Sender> sender, shared_ptr<Receiver> receiver) {
    u_int16_t sequence = 0;
    bool destination = false;
    vector<struct packet> received_packets;

    sender->set_ip_addr(ip_address);
    sender->set_pid(pid);
    sender->set_sockfd(sockfd);

    receiver->set_sockfd(sockfd);

    for (int ttl = 1; ttl <= MAX_TTL && !destination; ttl++) {

        for (int i = 0; i < MAX_PACKET_PER_TTL; i++)
            sender->send_packet(ttl, sequence++);

        time_point sending_time = std::chrono::high_resolution_clock::now();

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        struct timeval tv;
        tv.tv_sec = WAITING_TIME;
        tv.tv_usec = 0;

        while (received_packets.size() < MAX_PACKET_PER_TTL) {
            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);

            if (ready < 0)
                throw runtime_error("select error: waiting for the package in the socket has failed");

            if (ready == 0)
                break;

            struct packet packet = receiver->receive_packet();

            if (packet.id == pid && (packet.sequence / MAX_PACKET_PER_TTL + 1) == ttl && packet.ip_address != "") {
                received_packets.push_back(packet);
                if (packet.ip_address == ip_address)
                    destination = true;
            }
        }

        print_route(ttl, received_packets, sending_time);
        received_packets.clear();
    }
}

void Traceroute::print_route(u_int16_t ttl, vector<struct packet> received_packets, time_point sending_time) {
    printf("%2d. ", ttl);

    if (received_packets.size() == 0) {
        printf("* \n");
        return;
    }

    set<string> ip_addresses;

    for (auto packet: received_packets)
        ip_addresses.insert(packet.ip_address);

    for (auto ip_address : ip_addresses)
        printf("%-15s ", ip_address.c_str());

    if (received_packets.size() != MAX_PACKET_PER_TTL) {
        printf("??? \n");
        return;
    }

    u_int32_t sum_time = 0;
    for (auto packet : received_packets)
        sum_time += std::chrono::duration_cast<std::chrono::milliseconds>(packet.receipt_time - sending_time).count();

    printf("%ums \n", sum_time / 3);
}
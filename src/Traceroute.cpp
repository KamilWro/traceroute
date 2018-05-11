/* Kamil Breczko (280 990) */

#include "Traceroute.h"

Traceroute::Traceroute(u_int16_t pid) : pid(pid) {
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if (sockfd < 0)
        throw runtime_error(string("socket error: ") + strerror(errno));
}

void Traceroute::run(const char *ipAddress) {
    u_int16_t sequence = 0;
    bool destination = false;
    vector<Packet> receivedPackets;

    Sender sender(ipAddress, pid);
    Receiver receiver;

    for (u_int16_t ttl = 1; ttl <= MAX_TTL && !destination; ttl++) {

        for (int i = 0; i < MAX_PACKET_PER_TTL; i++)
            sender.sendPacket(sockfd, ttl, sequence++);

        time_point sendingTime = chrono::high_resolution_clock::now();

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        struct timeval tv{};
        tv.tv_sec = WAITING_TIME;
        tv.tv_usec = 0;

        while (receivedPackets.size() < MAX_PACKET_PER_TTL) {
            int ready = select(sockfd + 1, &descriptors, nullptr, nullptr, &tv);

            if (ready < 0)
                throw runtime_error("select error: waiting for the package in the socket has failed");

            if (ready == 0)
                break;

            Packet packet = receiver.receivePacket(sockfd);

            if (packet.id == pid && (packet.sequence / MAX_PACKET_PER_TTL + 1) == ttl && !packet.ipAddress.empty()) {
                receivedPackets.push_back(packet);
                if (packet.ipAddress == ipAddress)
                    destination = true;
            }
        }

        printRoute(ttl, receivedPackets, sendingTime);
        receivedPackets.clear();
    }
}

void Traceroute::printRoute(u_int16_t ttl, vector<Packet> receivedPackets, time_point sendingTime) {
    printf("%2d. ", ttl);

    if (receivedPackets.empty()) {
        printf("* \n");
        return;
    }

    set<string> ip_addresses;

    for (auto packet: receivedPackets)
        ip_addresses.insert(packet.ipAddress);

    for (const auto &ipAddress : ip_addresses)
        printf("%-15s ", ipAddress.c_str());

    if (receivedPackets.size() != MAX_PACKET_PER_TTL) {
        printf("??? \n");
        return;
    }

    u_int32_t sum_time = 0;
    for (auto packet : receivedPackets)
        sum_time += chrono::duration_cast<chrono::milliseconds>(packet.receiptTime - sendingTime).count();

    printf("%ums \n", sum_time / 3);
}

Traceroute::~Traceroute() {
    close(sockfd);
}

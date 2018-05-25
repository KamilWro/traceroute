/* Kamil Breczko (280 990) */

#include "Traceroute.h"

Traceroute::Traceroute(uint16_t pid) : pid(pid) {
    sockfd = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
}

void Traceroute::run(const char *ipAddress) {
    uint16_t sequence = 0;
    bool destination = false;
    vector<Packet> receivedPackets;

    Sender sender(ipAddress, pid);
    Receiver receiver;

    for (uint16_t ttl = 1; ttl <= MAX_TTL && !destination; ttl++) {

        for (int i = 0; i < MAX_PACKET_PER_TTL; i++)
            sender.sendPacket(sockfd, ttl, sequence++);

        time_point sendingTime = chrono::high_resolution_clock::now();

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);
        struct timeval tv{};
        tv.tv_sec = WAITING_TIME_S;
        tv.tv_usec = WAITING_TIME_US;

        while (receivedPackets.size() < MAX_PACKET_PER_TTL) {
            int ready = Select(sockfd + 1, &descriptors, nullptr, nullptr, &tv);

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

void Traceroute::printRoute(uint16_t ttl, vector<Packet> receivedPackets, time_point sendingTime) {
    cout << setw(2) << right << ttl << ". ";

    if (receivedPackets.empty()) {
        cout << "*" << endl;
        return;
    }

    set<string> ip_addresses;

    for (auto packet: receivedPackets)
        ip_addresses.insert(packet.ipAddress);

    for (const auto &ipAddress : ip_addresses)
        cout << setw(15) << left << ipAddress;

    if (receivedPackets.size() != MAX_PACKET_PER_TTL) {
        cout << "???" << endl;
        return;
    }

    u_int32_t sum_time = 0;
    for (auto packet : receivedPackets)
        sum_time += chrono::duration_cast<chrono::milliseconds>(packet.receiptTime - sendingTime).count();

    cout << sum_time / MAX_PACKET_PER_TTL << "ms" << endl;
}

Traceroute::~Traceroute() {
    Close(sockfd);
}
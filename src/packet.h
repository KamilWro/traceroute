/* Kamil Breczko (280 990) */

#ifndef PACKET_H
#define PACKET_H

#include <chrono>
#include <string>

typedef std::chrono::high_resolution_clock::time_point time_point;

struct packet {
    u_int16_t id;
    u_int16_t sequence;
    std::string ip_address;
    time_point receipt_time;

    packet(u_int16_t id, u_int16_t sequence, std::string ip_address, time_point receipt_time) :
            id(id), sequence(sequence), ip_address(ip_address), receipt_time(receipt_time) {}

};

#endif

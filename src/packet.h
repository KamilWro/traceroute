/*
 * Kamil Breczko
 * nr. indeksu: 280990
 */

#ifndef PACKET_H
#define PACKET_H

#include <chrono>
#include <zconf.h>

typedef std::chrono::high_resolution_clock::time_point time_point;

struct Packet {
    u_int16_t id;
    u_int16_t sequence;
    const char *ip_address;
    time_point receipt_time;

    Packet(u_int16_t id, u_int16_t sequence, const char *ip_address, const time_point &receipt_time) :
            id(id), sequence(sequence), ip_address(ip_address), receipt_time(receipt_time) {}
};

#endif

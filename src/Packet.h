/* Kamil Breczko (280 990) */

#ifndef PACKET_H
#define PACKET_H

#include <chrono>
#include <string>
#include <utility>

using namespace std;

typedef chrono::high_resolution_clock::time_point time_point;

typedef struct packet {
    u_int16_t id;
    u_int16_t sequence;
    string ipAddress;
    time_point receiptTime;

    packet(u_int16_t id, u_int16_t sequence, string ipAddress, time_point receipt_time) :
            id(id), sequence(sequence), ipAddress(move(ipAddress)), receiptTime(receipt_time) {}

} Packet;

#endif

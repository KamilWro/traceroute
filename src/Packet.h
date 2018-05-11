/* Kamil Breczko (280 990) */

#ifndef PACKET_H
#define PACKET_H

#include <chrono>
#include <string>

using namespace std;

typedef chrono::high_resolution_clock::time_point time_point;

struct Packet {
    u_int16_t id;
    u_int16_t sequence;
    string ipAddress;
    time_point receiptTime;

    Packet(u_int16_t id, u_int16_t sequence, const string &ipAddress, time_point receipt_time) :
            id(id), sequence(sequence), ipAddress(ipAddress), receiptTime(receipt_time) {}

};

#endif

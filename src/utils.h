/*
 * Kamil Breczko
 * nr. indeksu: 280 990
 */

#ifndef UTILS_H
#define UTILS_H

#include <zconf.h>
#include <chrono>
#include <vector>
#include <set>
#include <memory.h>
#include <arpa/inet.h>
#include <errno.h>

#include "packet.h"
#include <stdio.h>

#define MAX_TTL 30
#define MAX_PACKET_PER_TTL 3

typedef std::chrono::high_resolution_clock::time_point time_point;

bool is_valid_args(int argc, const char **argv);

void print_route(u_int16_t ttl, std::vector<Packet> received_packets, time_point point);

#endif

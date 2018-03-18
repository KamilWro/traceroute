/*
 * Kamil Breczko
 * nr. indeksu: 280990
 */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include <cstring>
#include <cerrno>
#include <cstdio>

#include "packet.h"

class Receiver {
  private:
    int sockfd;

    icmp *get_sent_icmp_header(u_int8_t *icmp_packet) const;

  public:
    Receiver(int sockfd);

    Packet receive_packet();
};


#endif

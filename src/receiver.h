/* Kamil Breczko (280 990) */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>

#include "packet.h"

class Receiver {
  private:
    int sockfd;

    struct icmp *get_sent_icmp_header(u_int8_t *icmp_packet) const;

  public:
    Receiver(int sockfd);

    struct packet receive_packet();
};


#endif

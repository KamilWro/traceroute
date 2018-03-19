/* Kamil Breczko (280 990) */

#ifndef RECEIVER_H
#define RECEIVER_H

#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <string.h>

#include "packet.h"
#include "receiver.h"

class Receiver_icmp : public Receiver {
  private:
    struct icmp *get_sent_icmp_header(u_int8_t *icmp_packet) const;

  public:
    ~Receiver_icmp() {};

    struct packet receive_packet();
};


#endif

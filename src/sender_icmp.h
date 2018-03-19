/* Kamil Breczko (280 990) */

#ifndef SENDER_H
#define SENDER_H

#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdexcept>
#include "sender.h"

class Sender_icmp : public Sender {
  private:
    u_int16_t compute_icmp_checksum(const void *buff, int length);

    struct icmphdr create_icmphdr(u_int16_t sequence);

  public:

    void send_packet(int ttl, u_int16_t sequence);

    ~Sender_icmp() {};
};


#endif

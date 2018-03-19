/* Kamil Breczko (280 990) */

#ifndef TRACEROUTE_SENDER_H
#define TRACEROUTE_SENDER_H

#include <string>

class Sender {
  protected:
    u_int16_t pid;
    const char *ip_addr;
    int sockfd;
  public:
    virtual void send_packet(int ttl, u_int16_t sequence) = 0;

    virtual ~Sender() {}

    void set_pid(u_int16_t pid) {
        Sender::pid = pid;
    }

    void set_ip_addr(const char *ip_addr) {
        Sender::ip_addr = ip_addr;
    }

    void set_sockfd(int sockfd) {
        Sender::sockfd = sockfd;
    }
};


#endif //TRACEROUTE_SENDER_H

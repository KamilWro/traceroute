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
        this->pid = pid;
    }

    void setIp_addr(const char *ip_addr) {
        this->ip_addr = ip_addr;
    }

    void setSockfd(int sockfd) {
        this->sockfd = sockfd;
    }
};


#endif //TRACEROUTE_SENDER_H

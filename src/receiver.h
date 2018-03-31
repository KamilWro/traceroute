/* Kamil Breczko (280 990) */

#ifndef TRACEROUTE_RECEIVER_H
#define TRACEROUTE_RECEIVER_H


class Receiver {
  protected:
    int sockfd;
  public:
    virtual struct packet receive_packet()=0;

    virtual ~Receiver() {}

    void setSockfd(int sockfd) {
        this->sockfd = sockfd;
    }

};


#endif //TRACEROUTE_RECEIVER_H

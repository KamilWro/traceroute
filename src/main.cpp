/* Kamil Breczko (280 990) */

#include "traceroute.h"
#include <unistd.h>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: incorrect number of arguments \n");
        return -1;
    }

    try {
        int pid = getpid();
        std::shared_ptr<Sender> sender_icmp(new Sender_icmp);
        std::shared_ptr<Receiver> receiver_icmp(new Receiver_icmp);

        Traceroute traceroute(pid);
        traceroute.run(argv[1], sender_icmp, receiver_icmp);
    } catch (const exception &e) {
        fprintf(stderr, "%s \n", e.what());
        return -1;
    }

    return 0;
}
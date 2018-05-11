/* Kamil Breczko (280 990) */

#include "Traceroute.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "error: incorrect number of arguments \n");
        return -1;
    }

    try {
        uint16_t pid = getpid();
        Traceroute traceroute(pid);
        traceroute.run(argv[1]);
    } catch (const exception &e) {
        fprintf(stderr, "%s \n", e.what());
        return -1;
    }

    return 0;
}
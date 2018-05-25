/* Kamil Breczko (280 990) */

#include "Traceroute.h"

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cerr << "error: incorrect number of arguments" << endl;
        return -1;
    }

    try {
        uint16_t pid = getpid();
        Traceroute traceroute(pid);
        traceroute.run(argv[1]);
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}
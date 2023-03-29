#include <time.h>

int sleep(unsigned int seconds) {
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0;
    while (nanosleep(&req, &rem) == -1) {
        req = rem;
    }
}
#include <time.h>

int sleep(unsigned int seconds) {
    // Create a timespec structure representing the requested sleep time
    struct timespec req, rem;
    req.tv_sec = seconds; // Set the number of seconds to sleep
    req.tv_nsec = 0;      // Set the nanoseconds to zero

    // Call the nanosleep function with the requested sleep time.
    // If nanosleep returns -1, it indicates that the sleep was interrupted 
    // by a signal. In this case, set the requested sleep time to the remaining 
    // sleep time and call nanosleep again
    while (nanosleep(&req, &rem) == -1) {
        req = rem;
    }

    return 0;
}
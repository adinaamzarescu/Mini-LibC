#ifndef MINI_LIBC_TIME_H
#define MINI_LIBC_TIME_H


struct timespec {
    long tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *req, struct timespec *rem);
int sleep(unsigned int seconds);

#endif //MINI_LIBC_TIME_H
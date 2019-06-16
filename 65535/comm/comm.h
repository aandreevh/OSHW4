#ifndef H_COMM
#define COMM

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <err.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define SEM_KEY 1654654
#define SHM_KEY 5465454

#define SHM_MEM 1024

#define SEM_COUNT 3
#define SEM_S 0  // client wait for server (mutex)
#define SEM_B1 1 // server wait for event (barrier)
#define SEM_B2 2 // client wait for event (barrier)

#define ASSERT(c, m) \
    if (!(c))        \
        err(1, m);

#define ASSERTX(c, m) \
    if (!(c))        \
        errx(1, m);


extern void ishm(bool);
extern void dshm(bool);
extern void *vshm();

#endif
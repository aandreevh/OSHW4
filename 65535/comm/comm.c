#include "comm.h"

static int shm_id = -1;
static void *shm_ptr = NULL;

static int sem_id = -1;

bool wsem(_sem sem)
{
    ASSERTX(sem_id != -1, "Sem not opened")
    return semop(sem_id, &(struct sembuf){sem, -1, SEM_UNDO}, 1) == -1 ? false : true;
}

bool sigsem(_sem sem)
{
    ASSERTX(sem_id != -1, "Sem not opened")
    return semop(sem_id, &(struct sembuf){sem, +1, SEM_UNDO}, 1) == -1 ? false : true;
}

extern void init(bool creat)
{
    isem(creat);
    ishm(creat);
}
extern void del(bool del)
{
    dsem(del);
    dshm(del);
}

void isem(bool creat)
{
    ASSERTX(sem_id == -1, "Sem already in use")

    ASSERT((sem_id = semget(SEM_KEY, SEM_COUNT, (creat ? IPC_CREAT | IPC_EXCL : 0) | 0666)) || creat, "Could not bind sem");

    if (sem_id == -1)
    {
        ASSERT((sem_id = semget(SEM_KEY, SEM_COUNT, 0666)) != -1, "Could not bind sem")
        ASSERT(semctl(sem_id, 0, IPC_RMID) != -1, "Could not remove sem")
        ASSERT((sem_id = semget(SEM_KEY, SEM_COUNT, (creat ? IPC_CREAT | IPC_EXCL : 0) | 0666)) != -1, "Could not recreate sem");
    }
    if (creat)
    {
        ASSERT(semctl(sem_id, SEM_S, SETVAL, 1) != -1, "Could not set sem value")
        ASSERT(semctl(sem_id, SEM_B1, SETVAL, 0) != -1, "Could not set sem value")
        ASSERT(semctl(sem_id, SEM_B2, SETVAL, 0) != -1, "Could not set sem value")
    }
}

void dsem(bool del)
{
    ASSERTX(sem_id != -1, "Sem not opened")
    if (del)
        ASSERT(semctl(sem_id, 0, IPC_RMID) != -1, "Could not close sem")
}

void ishm(bool creat)
{
    ASSERTX(shm_id == -1, "Shared memory already in use")

    ASSERT((shm_id = shmget(SHM_KEY, SHM_MEM_SIZE, (creat ? IPC_CREAT | IPC_EXCL : 0) | 0666)) || creat, "Could not bind shared memory")

    if (shm_id == -1)
    {
        ASSERT((shm_id = shmget(SHM_KEY, SHM_MEM_SIZE, 0666)) != -1, "Could not bind shared memory")
        ASSERT(shmctl(shm_id, IPC_RMID, NULL) != -1, "Could not allocate nor deallocate shared memory")
        ASSERT((shm_id = shmget(SHM_KEY, SHM_MEM_SIZE, (creat ? IPC_CREAT | IPC_EXCL : 0) | 0666)) != -1, "Could not alloc shared memory")
    }
}

void dshm(bool del)
{
    ASSERTX(shm_id != -1, "No shared memory created")
    shmdt(vshm());
    if (del)
        shmctl(shm_id, IPC_RMID, NULL);

    shm_id = -1;
}

void *vshm()
{
    ASSERTX(shm_id != -1, "No shared memory")
    if (shm_ptr == NULL)
        ASSERT((shm_ptr = shmat(shm_id, NULL, 0)) != (void *)-1, "Could not get shared mem ptr")

    return shm_ptr;
}
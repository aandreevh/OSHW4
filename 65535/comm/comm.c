#include "comm.h"

static int shm_id =-1;
static int sem_id =-1;

void ishm(bool creat){
if(shm_id == -1){
    
        shm_id = shmget(SHM_KEY,SHM_MEM,(creat ? IPC_CREAT | IPC_EXCL : 0) | 0666);

        if(shm_id == -1){
            ASSERT( (shm_id = shmget(SHM_KEY,SHM_MEM, 0666)) != -1,"Could not bind shared memory")
           ASSERT(shmctl(shm_id,IPC_RMID,NULL) !=-1,"Could not allocate nor deallocate shared memory")
           ASSERT(shmget(SHM_KEY,SHM_MEM,(creat ? IPC_CREAT | IPC_EXCL : 0) | 0666) !=-1,"Could not alloc shared memory")
        }
    
    }
}

void dshm(bool del){
    ASSERTX(shm_id != -1,"No shared memory created")
    shmdt(vshm());
    if(del)shmctl(shm_id,IPC_RMID,NULL);
}
void* vshm(){
    
}
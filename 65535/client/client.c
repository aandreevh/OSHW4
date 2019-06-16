#include <sys/ipc.h>
#include <sys/shm.h>    
#include <sys/sem.h>    
#include <inttypes.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <err.h>
int main(){
    /*srand(time(0));
    int shm = shmget(123,sizeof(uint16_t),IPC_CREAT | 0666);

    uint16_t* shmr_ptr = shmat(shm,0,0);

    printf("%u\n",*shmr_ptr);
    *shmr_ptr = rand()%1000;
     printf("%u\n",*shmr_ptr);

     shmdt(shmr_ptr);
     shmctl(shm,IPC_RMID,NULL);*/

        int sem = semget(1234,1,IPC_CREAT | 0666);

        semctl(sem,0,SETVAL,0);

        struct sembuf p = { 0, -1, SEM_UNDO}; //wait
        struct sembuf v = { 0, +1, SEM_UNDO}; //signal
        
     
      semop(sem, &v, 1);

     if( semctl(sem,0,IPC_RMID) <0)err(1,"WWW");

        
       
    return 0;
}
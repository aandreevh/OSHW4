#include <sys/ipc.h>
#include <sys/shm.h>    
#include <sys/sem.h>    
#include <inttypes.h>
#include <sys/types.h>
#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <err.h>

#include "comm.h"

int main(){
   init_server();
   close_server();
}



void init_server(){
    ishm(true);
}
void close_server(){
    dshm(true);
}
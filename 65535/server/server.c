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

_fd fid;

const uint32_t BANK_STAT[MAX_ACC] = {0};

void ofile(const char *file)
{
    ASSERT((fid = open(file, O_CREAT | O_RDWR, 0666)) != -1, "Could not open/create file")

    struct stat st;
    ASSERT(fstat(fid,&st) != -1 ,"Could not read fstat")

    ASSERT(st.st_size ==0 || st.st_size == sizeof(BANK_STAT),"Invalid file size")
    if(st.st_size ==0){
        ASSERT(write(fid,BANK_STAT,sizeof(BANK_STAT))== sizeof(BANK_STAT), "Could not write bank data");
    }
}

bool verifyAccount(char acc){
    return acc-'A' < MAX_ACC;
}


bool accountValue(char acc,int16_t val,uint32_t* out){
    if(!verifyAccount(acc))return false;

    uint8_t acc_id = acc-'A';
    uint32_t accVal;

    ASSERT(lseek(fid,acc_id*sizeof(accVal),SEEK_SET) != -1,"Could not seek in file")
    ASSERT(read(fid,&accVal,sizeof(accVal)) == sizeof(accVal),"Could not read bank account")

    if(!( val >=0 || (val <0 && accVal > -val) )) return false;

    accVal += val;

    ASSERT(lseek(fid,acc_id*sizeof(accVal),SEEK_SET) != -1,"Could not seek in file")
    ASSERT(write(fid,&accVal,sizeof(accVal)) == sizeof(accVal),"Could not write file")

    if(out != NULL)*out = accVal;

    return true;
}

void cfile()
{
    ASSERT(close(fid) != -1, "Could not close file")
}

void init_server(size_t argc,const char* argv[])
{
    ASSERTX(argc == 2,"Invalid argument")

    ofile(argv[1]);
    init(true);
}
void close_server()
{
    printf("Closing server...\n");
    del(true);
    cfile();
}

int main(size_t argc,const char* argv[])
{
    atexit(close_server);
    init_server(argc,argv);

    uint32_t acc;
    accountValue('A',17,&acc);

    printf("%u\n",acc);

    memset(vshm(), 0, SHM_MEM_SIZE);
    //printf("%u", wsem(SEM_B1));
   
}

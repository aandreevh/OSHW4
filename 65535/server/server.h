#ifndef H_SERVER
#define SERVER

#include "comm.h"
#include<stdio.h>
#include <stdlib.h>


#define MAX_ACC 8

#define CODE_EXIT -1

struct shm_rep_impl
{
    int8_t code;
    uint8_t bytes[SHM_MEM_SIZE - sizeof(uint8_t)];
};

typedef struct shm_rep_impl shm_rep;


#endif
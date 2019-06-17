#include "client.h"

void init_client(){
  init(false);
}

void close_client(){
  del(false);
}

void transact(char acc,int16_t amount,shm_rep* output){
  ASSERTX(verifyAccount(acc),"Invalid account")

  //ASSERT(wsem(SEM_S),"Could not wait at gateway")
  
  shm_rep* shm = vshm();

  shm->code = CODE_NORM;
  memcpy(&shm->bytes,&acc,sizeof(char));
  memcpy(&shm->bytes +1,&amount,sizeof(int16_t));

  ASSERT(ssem(SEM_B1),"Could not wait at server response")
  ASSERT(wsem(SEM_B2),"Could not wait at server response")
  
  memcpy(output,shm,sizeof(shm_rep));

  ASSERT(ssem(SEM_S),"Could not free gateway")
}

void manageTransact(shm_rep* output){
  const char* errmsg = (const char*)&output->bytes;
  ASSERTX(output->code == CODE_NORM,errmsg)

  printf("Amount: %d\n",*(uint32_t*)&output->bytes);
}
int main(int argc,char* argv[]){

  ASSERTX(argc == 2,"Invalid argument count")
  ASSERTX(strlen(argv[1])==1,"Invalid argument")
  ASSERTX(argv[1][0] >='A' && argv[1][0]<='H',"Invalid account")

    atexit(close_client);
    init_client();

    shm_rep output;
    transact(argv[1][0],0,&output);
    manageTransact(&output);

    int16_t val;
    scanf("%"SCNd16,&val);
    


    transact(argv[1][0],val,&output);
    manageTransact(&output);
    return 0;
}



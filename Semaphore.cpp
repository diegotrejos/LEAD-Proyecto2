#include "Semaphore.h"

#define KEY 0xB57414

using namespace std;

Semaphore::Semaphore(int n){
	id = semget(KEY,1,IPC_CREAT|0600);
	if(id == -1){
		exit(1);
	}
	count = n;
	semctl(id,1,SETVAL,count);
}

Semaphore::~Semaphore(){
	semctl(id,0,IPC_RMID);
}

void Semaphore::notify(){
    struct sembuf z;
    z.sem_num= 0;
    z.sem_op= +1;  // Para el signal solo se cambia esto por +1
    z.sem_flg = IPC_NOWAIT;
    semop(id,&z,1);
    ++count;
}

void Semaphore::wait(){
    struct sembuf z;
    z.sem_num= 0;
    z.sem_op= -1;  // Para el signal solo se cambia esto por +1
    z.sem_flg = IPC_NOWAIT;
    semop(id,&z,1);
    --count;
}

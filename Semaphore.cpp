#include "Semaphore.h"

using namespace std;

Semaphore::Semaphore(int n, key_t key){
	id = semget(key,1,IPC_CREAT|0600);
	if(id == -1){
		exit(1);
	}
	count = n;
	while(count > 0){
		notify();
		--count;
	}
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
}

void Semaphore::wait(){
    struct sembuf z;
    z.sem_num= 0;
    z.sem_op= -1;  // Para el signal solo se cambia esto por +1
    z.sem_flg = IPC_NOWAIT;
    semop(id,&z,1);
}



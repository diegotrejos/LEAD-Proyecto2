#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <sys/types.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/sem.h>

        
class Semaphore {
	
public:

    Semaphore (int n = 0, key_t key = 0xA00000);
    ~Semaphore ();
    
    void notify();
    void wait();
    
private:

	int id;
    int count;
    
};

#endif // SEMAPHORE_H

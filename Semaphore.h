#include <sys/types.h>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/sem.h>

        
class Semaphore {
	
public:

    Semaphore (int n = 0);
    ~Semaphore ();
    void notify();
    
    void wait();
    
private:

	int id;
    int count;
    
};

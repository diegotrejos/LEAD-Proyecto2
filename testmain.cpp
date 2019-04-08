#include <algorithm>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Emisor.h"
#include "Semaphore.h"
#include "Buzon.h"

#define KEY 0xB57414

using namespace std;

Semaphore* contrat_ctrl; //semaforo para controlar la cantidad de contratistas
Buzon* bzn;

int main()
{
	
	 
   Emisor* emi = new Emisor();
	Buzon* buzon_emisor = new Buzon(KEY);
	bool trabajando = true;
	while(trabajando == true)
		{	
					
			//buzon q no logre usar  que retorn el veector<char> imagen
			buzon_emisor->recibir();
			//buzon_emisor->msgbuf.mText;
			
			

			emi->recibe(buzon_emisor->miBuzon.mText);

			//trabajando=false;//algo para frenarlo hay q definir eso
 		}	
	 
	return 0;
}
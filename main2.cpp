#include "Buzon.h"
#include <iostream>
int main(){
	key_t key = 0xB57414;
	Buzon* buzon = new Buzon(key);
	std::cout << "Esperando mensaje ... \n";
	
	while(true){
		buzon->recibir();
	}
	//free(buzon);
}

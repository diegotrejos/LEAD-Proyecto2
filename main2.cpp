#include "Buzon.h"
#include <iostream>
#include <fstream>
int main(){
	key_t key = 0xB57414;
	Buzon* buzon = new Buzon(key);
	std::cout << "Esperando mensaje ... \n";
	int size = 0;
	std::ofstream of("resultados/imagen.jpg", std::ofstream::app);
	int mensajesRec = 0;
	while(true){
		size = buzon->recibir();
		++mensajesRec;
		printf("Cantidad de mensajes recibidos: %d\n", mensajesRec);
		of.write(buzon->miBuzon.mText, size - 1);
	}
	//free(buzon);
}

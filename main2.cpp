#include "Buzon.h"
#include <iostream>
#include <fstream>
int main(){
	key_t key = 0xB57414;
	Buzon* buzon = new Buzon(key);
	std::cout << "Esperando mensaje ... \n";
	int size = 0;
	std::ofstream of("resultados/imagen.jpg", std::ios::out | std::ios::binary);
	int mensajesRec = 0;
	while(true){
		size = buzon->recibir();
		size = buzon->miBuzon.mensajeUtil;
		++mensajesRec;
		printf("Cantidad de mensajes recibidos: %d y el tamano del paquete es %d\n", mensajesRec, size);
		of.write(buzon->miBuzon.mText, size);
	}
	//free(buzon);
}

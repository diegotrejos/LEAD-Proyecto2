#include "Buzon.h"
#include <iostream>
#include <fstream>
int main(){
	key_t key = 0xB60513;
	Buzon* buzon = new Buzon(key);
	std::cout << "Esperando mensaje ... \n";
	int size = 0;
	int mensajesRec = 0;
	while(true){
		std::ofstream of("resultados/prueba.jpg", std::ios::out | std::ios::binary | std::ios::app);
		int size1 = buzon->recibir(1);
		size = buzon->miBuzon.mensajeUtil;
		++mensajesRec;
		std::cout << buzon->miBuzon.mText << std::endl;
		printf("Cantidad de mensajes recibidos: %d y el tamano del paquete es %d\n", mensajesRec, size);
		of.write(buzon->miBuzon.mText, size);
		of.close();
	}
	
	//free(buzon);
}

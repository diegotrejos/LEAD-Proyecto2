#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h> 
#include <string.h>
#include <iterator>

#include "Buzon.h"

using namespace std;
class Emisor
{
public:

	Emisor(Buzon* miBuzon);
	void recibe();//recibe datos del buzon
	void envio();//para sockets despues
	void escribir(char tag);//escribe en archivo ya abierto
//	void creaArchivo(char* nombre);//abre archivo nuevo
	~Emisor();
	int contador;
	Buzon* bzn;
	map<char,char*> archivos;//podria hacer mapas, tengo tag y nombre de archivo

};

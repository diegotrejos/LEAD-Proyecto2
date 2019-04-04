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

using namespace std;
class Emisor
{
public:

	 Emisor();
	void recibe(vector<char>);//recibe datos del buzon
	void envio();//para sockets despues
	void escribir(char tag, vector<char>);//escribe en archivo ya abierto
	void creaArchivo(char tag, char* nombre);//abre archivo nuevo
	~Emisor();
	map<char,char*> archivos;//podria hacer mapas, tengo tag y nombre de archivo

};
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <vector>
using namespace std;
class Emisor
{
public:
	Emisor();
	void recibe();//recibe datos del buzon
	void Envio();
	void archivar(vector<char>);//transforma datos a archivo
	void ordene();//ordena los paquetes de informacion y los manda a archivar
	void escribir(vector<char> result);
	
{

	~Emisor();

};
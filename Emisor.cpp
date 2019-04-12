#include "Emisor.h"
//#include "Buzon.h"
#define PAQSIZE 133


Emisor::Emisor()
{
	buildSocket();
}

void Emisor::buildSocket()
{
	cout << "Ingrese la direccion IP del servidor\n";
	string IP;
	cin >> IP;
	int port = 0;
	cout << "Ingrese el puerto por el que se comunicaran\n";
	cin >> port;
	this->s.Connect( IP.c_str(), port );// Se realiza la conexion segun la IP de la máquina
}

void Emisor::envio(char* buffer) // con sockets hacia receptor
{
	int st = this->s.Write(buffer, PAQSIZE);
}

void Emisor::recibe(char tag,char* paq,  int paq_size)
{
	char buffer[PAQSIZE];
	memcpy(buffer, paq, 128);
	buffer[128] = tag;
	int pos = 131;
	for (int i = 0; i < 3; ++i){
		int digit = paq_size % 10;	
		std::cout << digit << std::endl;
		sprintf (&buffer[pos], "%d", digit);
		std::cout << buffer[pos] << std::endl;
		paq_size /= 10;
		--pos;
	}
	buffer[132] = paq[128];
	envio(buffer);
}

Emisor::~Emisor()
{
	
}

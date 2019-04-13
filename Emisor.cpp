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

void Emisor::recibe(char tag, char* paq,  int paq_size)
{
	char buffer[133];
	cout << "Emisor recibi: " << paq << "y tiene tamano util: " << paq_size << endl;
	memcpy(buffer, paq, 128);
	buffer[128] = tag;
	buffer[129] = 'a';
	buffer[130] = 'a';
	buffer[131] = 'a';
	cout << "Bufer antes de meter tam: " << buffer << endl;
	int pos = 131;
	for (int i = 0; i < 3; ++i){
		int digit = paq_size % 10;
		cout << "Digit: " << digit << endl;	
		sprintf (&buffer[pos], "%d", digit);
		cout << "Armando buffer: " << buffer << endl;
		paq_size /= 10;
		--pos;
	}
	buffer[132] = paq[128];
	cout << "Emisor voy a enviar: " << buffer << endl;
	envio(buffer);
}

Emisor::~Emisor()
{
	
}

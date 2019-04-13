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
	cout << "Tamano util: " << buffer[129] << buffer[130] << buffer[131] << endl;
	int st = this->s.Write(buffer, PAQSIZE);
}

void Emisor::recibe(char tag, char* paq,  int paq_size)
{
	char buffer[133];
	for (int i = 0; i < 133; ++i){
		buffer[i] = 's';
	}
	cout << buffer << endl;
	cout << "Emisor recibi: " << paq << "y tiene tamano util: " << paq_size << endl;
	memcpy(buffer, paq, 128);

	cout << "Bufer antes de meter tam: " << buffer << endl;
	int pos = 131;
	for (int i = 0; i < 3; ++i){
		int digit = paq_size % 10;
		sprintf (&buffer[pos], "%d", digit);
		cout << "Armando buffer: " << buffer[pos] << endl;
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

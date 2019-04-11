#include "Socket.h"
#include <iostream>
using namespace std;
int main(){
	string ip;
	cout << "Ingrese el ip del servidor\n";
	cin >> ip;
	int port = 0;
	cout << "Ingrese el puerto por el que se comunicaran\n";
	cin >> port;
	Socket s;
	s.Connect( ip.c_str(), port );
	int st = 0;
	char buffer[120] = "Hola mensaje enviado";
	st = s.Write( buffer, 120 );
	cout << "Mensaje enviado: " << buffer << endl;
}

#include <iostream>
#include "Socket.h"
using namespace std;
int main(){
	Socket s1;	// se crea un socket de tipo SOCK_STREAM
	
	int port = 0;
	cout << "Ingrese el puerto por el que se comunicaran\n";
	cin >> port;
   	s1.Bind( 5050 );// puerto en el que va a recibir las solicitudes
   	cout << "Listening...\n";
   	s1.Listen( 3 );
   	
   	Socket* s2 = s1.Accept();// se espera una conexion
	printf("Conexion Aceptada \n");
	char buffer[120];
	s2->Read( buffer, 120 );
	cout << buffer << endl;
}

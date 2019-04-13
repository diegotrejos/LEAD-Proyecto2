#include <unistd.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iterator>
#include "Socket.h"

using namespace std;
class Emisor
{
public:
	Emisor();
	void recibe( char tag,char* paq, int paq_size);//recibe datos del buzon
	void envio(char* buffer); // Envio de paquete con socket
	~Emisor();
	Socket s;
	void buildSocket();
};

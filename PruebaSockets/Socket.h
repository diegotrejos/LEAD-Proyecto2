#ifndef SOCKET_H
#define SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <netdb.h>

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Socket{

  private:
	int descriptor;
	Socket* nuevo;

  public:

	Socket();
	Socket(int fd);
    ~Socket();
    int Connect(const char* Host, int Port);
	int Read(char* text, int len);
	int Write(char* text, int len);
	int Shutdown(int shutType);

	int Listen(int Queue);
	int Bind(int Port);
	Socket* Accept();

	int Close();

	//char * getHostIP(char*);
	
};

#endif // SOCKET_H

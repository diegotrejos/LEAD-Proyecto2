#include "Socket.h"
#include <iostream>
//constructor
Socket:: Socket(){
	if ((descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(1); 
    } 
    cout << "Descriptor = " << descriptor << endl;
}

Socket::Socket(int fd){
	descriptor = fd;
}

//destrutor
Socket::~Socket(){
	close(descriptor);
}

int Socket::Connect(const char* Host, int Port){
	struct sockaddr_in host_addr;
	host_addr.sin_family = AF_INET;
	inet_aton( Host,  &host_addr.sin_addr );
	host_addr.sin_port = htons( Port );
	return connect( descriptor, (sockaddr *) & host_addr, sizeof( host_addr ));
}
int Socket::Read(char* text, int len){
	return read(descriptor, text, len);
}
int Socket::Write(char* text, int len){
	return write(descriptor, text, len);
}
int Socket::Shutdown(int shutType){
	return shutdown(descriptor, shutType);
}

int Socket::Close(){
	return close(descriptor);
}

int Socket::Listen(int Queue){
	return listen(descriptor, Queue);
}

int Socket::Bind(int Port){
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	server_addr.sin_port = htons( Port );
	
	int len = sizeof( server_addr );
	return bind( descriptor, (const sockaddr *) & server_addr,len );
}

Socket* Socket::Accept(){
	struct sockaddr host_addr;
	socklen_t len = sizeof(host_addr);
	int fdResult = accept(descriptor,(sockaddr*) & host_addr,&len);
	if(fdResult >=0){
		nuevo = new Socket(fdResult);
	}
	else{
		nuevo = 0;
	}	
	return nuevo;
}
/*char * Socket::getHostIP(char* host){
	struct hostent * temporal;
	temporal = gethostbyname(host);
	return inet_ntoa(*(struct in_addr*)(temporal->h_addr));
	
}*/


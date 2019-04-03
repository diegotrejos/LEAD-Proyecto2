#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

#include "Semaphore.h"
#include "Buzon.h"

#define KEY 0xB57414

using namespace std;

Semaphore* contrat_ctrl; //semaforo para controlar la cantidad de contratistas
Buzon* bzn;

bool test_directory(char* directorio);
void leerBytes(char const* imagen);
int crearSocket();
int filter_function(const struct dirent *dir);
int lector(char* directorio);

int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "Es necesario indicar el directorio" << endl;
		return(1);
	}
	
	/*
     if(fork() == 0){ Lector
	 
	 } else{ //Emisor
	 
	 }
	*/
	
	
	//contenido de lector.
	char* directorio;
	directorio = argv[1];
	cout << "antes de crear semaforo" << endl;
	contrat_ctrl = new Semaphore(2, KEY);
	cout << "después de crear semaforo" << endl;
	int success = lector(directorio);
	if(success != 0){
		free(contrat_ctrl);
		return 1;
	}
	free(contrat_ctrl);
	return 0;
}

bool test_directory(char* directorio){
	DIR* work_bench = opendir(directorio);
	if(!work_bench){
		return false;
	} else{
		closedir(work_bench);
		return true;
	}
}

int crearSocket() 
{
	// Codigo servidor
	/*int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
    char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) // Verificacion de creacion del socket
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 

        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    valread = read( new_socket , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(new_socket , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); */
    
    
    
    // ************************ Codigo cliente ********************
    /*struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );
    */
	return 0;
}

int filter_function(const struct dirent *dir){
	if(((strstr(dir->d_name, ".png") || strstr(dir->d_name, ".jpg")) || ((strstr(dir->d_name, ".jpeg")) || (strstr(dir->d_name, ".gif")))) || ((strstr(dir->d_name, ".JPEG")))){
		return 1;
	} else{
		return 0;
	}
}

int lector(char* directorio){
	if(!test_directory(directorio)){ // Revisa si el posible abrir el directorio
		std:: cout << "Fallo al abrir el directorio\n";
		return 1;
	}
	
	struct dirent** imagenes; // Estructura que guarda la posicion de memoria y el nombre de las imagenes
	int n,i;
	n = scandir(directorio, &imagenes, filter_function, versionsort);
	if (n < 0)
        perror("scandir");
    else
    {
		cout << n << endl;
        for(i =0 ; i < n; ++i)
        {
			contrat_ctrl->wait();
			cout << i << endl;
			if(fork() == 0){
				//printf("%ld %s\n",imagenes[i]->d_ino, imagenes[i]->d_name);
				leerBytes(strcat(directorio, imagenes[i]->d_name));
				free(imagenes[i]);
            }
        }
        free(imagenes);
    }
    
    // Crear contratistas y seguir contratando hasta que no hayan mas imagenes por analizar
	return 0;
}


void leerBytes(char const* imagen)
{
	// Esto lee toda la imagen
	
	cout << getpid() << " "<< imagen << endl;
	ifstream ifs(imagen, ios::binary|ios::ate); //objeto ifstream en binario
	ifstream::pos_type pos = ifs.tellg(); // tellg() dice el tamaño, por ende pos es el tamaño del archivo.

	std::vector<char> result(pos); //vector de 512 bytes
	
	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);
	
	contrat_ctrl->notify();
	exit(0);
}

/*
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define MSGSZ 128 ********************** Message rec

// Declare the message structure.
typedef struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
} message_buf;

main()
{
	int msqid;
	key_t key;
	message_buf rbuf;

	key = 2234;

	if ((msqid = msgget(key, 0666)) < 0) {
		perror("msgget");
		exit(1);
	}

	// Receive an answer of message type 1.
	if (msgrcv(msqid, &rbuf, MSGSZ, 1, 0) < 0) {
		perror("msgrcv");
		exit(1);
	}

	printf("^%s\n", rbuf.mtext);
	exit(0);
}










/* ********************** message send
int main(int argc, char* argv[]){
	// Se pasa el directorio con las imagenes como argumento del programa
	if(argc != 2){ // Revisa si pasaron la carpeta como argumento del programa
		return std::cerr << "Para utilizar el programa de manera correcta debe ingresar la carpeta con las imagenes como argumento del programa\n";
	}
	
	lector(argv[1]);
    return 0;
}




*/

/*
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MSGSZ 128	

// Declare the message structure

typedef struct msgbuf {
	long mtype;
	char mtext[MSGSZ];
} message_buf;

main() 
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	message_buf sbuf;
	size_t buf_length;

	key = 2234;

	(void)fprintf(stderr, "\nmsgget: Calling msgget(%#1x,\%#o)\n", key, msgflg);
	
	if ((msqid = msgget(key, msgflg)) < 0) {
		perror("msgget");
		exit(1);
	}
	else
		(void)fprintf(stderr, "msgget: msgget succeeded: msgqid = %d\n", msqid);

	// We'll send message type 1 
	sbuf.mtype = 1;
	(void) fprintf(stderr, "msggeet: msgget succeeded: msqid = %d\n", msqid);
	(void) strcpy(sbuf.mtext, "Did you get this?");
	(void) fprintf(stderr, "msgget: msgget succeeded: msqid = %d\n", msqid);

	buf_length = strlen(sbuf.mtext) + 1;

	// Send a message.
	if((msgsnd(msqid, &sbuf, buf_length, IPC_NOWAIT)) < 0){
		printf("%d, %d, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buf_length);
		perror("msgsnd");
		exit(1);
	}
	else
		printf("Message: \"%s\" Sent\n", sbuf.mtext);

	exit(0);
}
*/

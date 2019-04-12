#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h> 
#include <string.h>
#include <sstream>
#include <iterator>
#include <thread>
#include <queue>
#include "Semaphore.cpp"
#include "Socket.h"
#define MAX 132

#define KEY 0xB57414

using namespace std;
typedef struct{
	char[128] data;
	char tag;
	int utiles;
} bytes;

map<char,char*> archivos;//regista los archivos existentes
int contador=0;//cuenta los archivos q van entrando
bool finished;
std::queue<bytes>* myqueue;
Semaphore* main_semaphore;
std::vector<std::queue<bytes>> thread_queues;
std::vector<Semaphore> thread_semaphores;
std::vector<std::thread> threads;

void escribir()
{
	//acá se crea el archivo
	//bool imagen_terminada
	//entra en un while(!imagen_terminada)
	//semaforo para esperar a que hayan objetos en la cola.
	//escribir en el archivo desde la cola.
	//if(bytes.utiles < 128) bool imagen_terminada = true;
}

void creaArchivo(char tag, char* dato, int util_size)//crea archivo nuevo
{
	char* nombre;   
    for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
    { 
        if(tag == itr->first)
        {
            nombre = itr->second;
        }
    }


    cout<<"creando archivo "<< nombre <<endl;
    ofstream of (nombre, ios::out | ios::binary);
    int tam = util_size;
    //char* c = &dato[0];
    of.write(dato, tam);
    of.close();
}

void escribir(char tag, char* datos, int util_size)//continua escribiendo en archivo existente
{
    char * nombre;
    for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
     { 
        if(tag == itr->first)
        {
            nombre = itr->second;
        }
    } 
    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

    ofstream of;  // Create Object of Ofstream
    of.open (nombre, ios::app); // Append mode
    int tam = util_size;

    of.write(datos, tam);
    of.close(); // Closing the file

}


void archivar(/*char tag,char* paq,  int paq_size*/) //este mae se va a encargar de ver si el tag es nuevo para ver que hace con los datos.
{
	char tag = queue.front().tag;
	char* paq = queue.front().data;
	int paq_size = queue.front().utiles;
    bool nuevo= true;//decide si el tag es nuevo
        
    //cout<<"tag: "<< tag <<" ."<<endl;
    
    for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
    { 
        
        if(tag == itr->first)
        {
            nuevo =false;
            //cout<<"tag: "<<tag<<" es igual a: "<<itr->first<<" que ya esta reistrado y tiene su arhcivo que se llama: "<<itr->second<<endl;;
        }
    } 


    if(nuevo ==true)//si el tag es nuevo crea archivo
    { //OJO!!! Si el tag es nuevo, hay que crear un hilo nuevo, un semáforo y una cola en el vector
		//CREAR HILO: thread_queues.pushback( new std::thread(escribir) )
		// thread_queues[pos].detach()
        contador++;
        string nombre_archivo="resultados/imagen";
        string Ccontador=to_string(contador);
        Ccontador=nombre_archivo+Ccontador;
        char* a = new char[Ccontador.size()];
        strcpy (a, Ccontador.c_str());

        archivos.insert(pair<char,char*>(tag,a));//el nombre del archivo es el resto del paquete

        creaArchivo(tag,paq,paq_size);
    }   
        
    else//si no es nuevo escribe en uno existente
    {
		escribir(tag,paq,paq_size);
    }
    //contador++;
}


void extraeDatos(char* datos)
{
	char tag = datos[128];
	cout<<"tag: "<<tag<<endl;
	int tam_util= 0;
	char part[3];
	char data[128];
	memcpy(part, datos + 129 /* Offset */, 3 /* Length */);
	memcpy(data, datos, 128);
	tam_util = atoi(part);
	cout<<"Size util: "<<tam_util<<endl;
	
	//archivar(tag,datos,tam_util);
	bytes b;
	strcpy(b.data, data);
	b.tag = tag;
	b.utiles = tam_util;
	myqueue->push(b);
}


void recibe(int espera)
{
    Socket s1;  // se crea un socket de tipo SOCK_STREAM
    cout << "Ingrese el puerto por el que se comunicaran\n";
    int port = 0;
    cin >> port;
    char buffer[MAX];
    
    s1.Bind(port);// puerto en el que va a recibir las solicitudes
    s1.Listen( 3 );
    
    Socket* s2 = s1.Accept();// se espera una conexion
    printf("Conexion Aceptada \n");
	while(true){
		s2->Read( buffer, MAX );
		extraeDatos(buffer);
		std::this_thread::sleep_for(std::chrono::seconds(espera));
	}
}


int main()
{
	myqueue = new queue<bytes>();
	thread_queues = new vector<std::queue<bytes>>();
	thread_semaphores = new vector<Semaphore>();
	threads = vector<std::thread>();
	main_semaphore = new Semaphore(0,KEY);
	std::thread recolector(recibe, 1);
	recolector.detach();
	std::thread separador(archivar);
	separador.detach();
	while(!finished){
	}
    return 0;
}

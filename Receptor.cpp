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
#include "Buzon.h"


#define MAX 133

#define KEY 0xB57414

using namespace std;
typedef struct{
    char data[128];
    char tag;
    int utiles;
    char ultimo;
} bytes;

map<char, int> tags;//regista los tags con sus hilos
int contador=0;//cuenta los archivos q van entrando
bool finished;
/*std::queue<bytes>* myqueue;
Semaphore* main_semaphore;
std::vector<std::queue<bytes>> thread_queues;
std::vector<Semaphore> thread_semaphores;
std::vector<std::thread> threads;
*/

void creaArchivo(char tag, char* dato, int util_size, char *nombre)//crea archivo nuevo
{
   

    cout<<"creando archivo "<< nombre <<endl;
    ofstream of (nombre, ios::out | ios::binary);
    int tam = util_size;
    //char* c = &dato[0];
    of.write(dato, tam);
    of.close();
}

void escribir(char tag, char* datos, int util_size, char* nombre)//continua escribiendo en archivo existente
{
   
    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

    ofstream of;  // Create Object of Ofstream
    of.open (nombre, ios::app); // Append mode
    int tam = util_size;

    of.write(datos, tam);
    of.close(); // Closing the file

}

void hilo_escribir(bytes const  &b)
{
    int contador=999;
    for (auto itr = tags.begin(); itr != tags.end(); ++itr)//revisa que no exista este tag
    { 
        
        if(b.tag == itr->first)
        {
         
            contador=itr->second;
            cout<<"tag: "<<b.tag<<" en el hilo: "<<itr->second<<endl;
        }
    }

       
        string nombre_archivo="resultados/imagen";
        string Ccontador=to_string(contador);
        Ccontador=nombre_archivo+Ccontador;
        char nombre[Ccontador.size()];
        strcpy (nombre, Ccontador.c_str());


    
  
   
    creaArchivo(b.tag, b.data, b.utiles, nombre);
    bool imagen_terminada = false;
    
    while(!imagen_terminada)
    {
    
    //buzon receive() con vector y datos  
    //escribir(miMensaje.tag,miMensaje.data,miMensaje.util, nombre);
    //if(miMensaje.utiles < 128) bool imagen_terminada = true;
    }
}


void archivar(bytes b) //este mae se va a encargar de ver si el tag es nuevo para ver que hace con los datos.
{
    char tag = b.tag;
    char* data = b.data;
    int utiles = b.utiles;
    bool nuevo=true;//decide si el tag es nuevo
    int hilo=0;    
    //cout<<"tag: "<< tag <<" ."<<endl;
    
    for (auto itr = tags.begin(); itr != tags.end(); ++itr)//revisa que no exista este tag
    { 
        
        if(tag == itr->first)
        {
            nuevo =false;
            hilo=itr->second;
            //cout<<"tag: "<<tag<<" es igual a: "<<itr->first<<" que ya esta reistrado y tiene su arhcivo que se llama: "<<itr->second<<endl;;
        }
    } 


    if(nuevo ==true)//si el tag es nuevo crea archivo*************************8
    { //OJO!!! Si el tag es nuevo, hay que crear un hilo nuevo, un semáforo y una cola en el vector
        //CREAR HILO: thread_queues.pushback( new std::thread(escribir) )
        // thread_queues[pos].detach()
      

        tags.insert(pair<char,int>(tag,contador));
        contador++;
        std::thread worker(hilo_escribir,b);
        worker.detach();
        //el nombre del archivo es el resto del paquete
        //*******crea hilo  y llama a metodo hilo_escribir(tag,data,dara_util, nombre);
        //pthread_create(contador, NULL, hilo_escribir(tag,data,utiles, nombre), NULL);
    }   
        
    else//si no es nuevo escribe en uno existente
    {
        cout<< "Su hilo es:"<< hilo << endl;
     //envia con buzon (tag,data,dara_util)   
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
    char fin = datos[132];
    cout<<"Size util: "<<tam_util<<endl;

    bytes b;
    strcpy(b.data, data);
    b.tag = tag;
    b.utiles = tam_util;
    b.ultimo = fin;
    archivar(b);//AQUI envia por el buzon
    
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
    while(true)
    {
        s2->Read( buffer, MAX );
        extraeDatos(buffer);
        std::this_thread::sleep_for(std::chrono::seconds(espera));
    }
}





int main()
{
  //recibe(0);

    //myqueue = new queue<bytes>();
    //thread_queues = new vector<std::queue<bytes>>();
    //thread_semaphores = new vector<Semaphore>();
    //threads = vector<std::thread>();
    //main_semaphore = new Semaphore(0,KEY);
    //std::thread recolector(recibe, 1);
    //recolector.detach();
    //std::thread separador(archivar);
    //separador.detach();
    //while(!finished){

    //}
    return 0;
}






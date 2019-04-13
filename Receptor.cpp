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
#define KEY 0xB73404

using namespace std;
/*typedef struct{
    char data[128];
    char tag;
    int utiles;
    char ultimo;
} bytes;*/

long tipoMenMap = 1;
Buzon* buz = new Buzon(KEY); // Buzon que va a guardar paquetes recibidos
map<char, long> tags; // Registra los tags con sus hilos
long contadorArchivos = 1; // Cuenta los archivos que van entrando
bool finished;
std::vector<std::thread> threads;


void creaArchivo(char tag, char* dato, int util_size, char *nombre) //crea archivo nuevo
{
    cout << "creando archivo " << nombre << endl;
    ofstream of (nombre, ios::out | ios::binary);
    //char* c = &dato[0];
    of.write(dato, util_size);
    of.close();
}

void escribir(char tag, char* datos, int util_size, char* nombre)//continua escribiendo en archivo existente
{
   
    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

    ofstream of;  // Create Object of Ofstream
    of.open (nombre, ios::app); // Append mode

    of.write(datos, util_size);
    of.close(); // Closing the file

}

void hilo_escribir(long tipoMensaje, char* dato, int util_size, char* nombre)
{
    Buzon* buzThread = new Buzon(KEY); // Cada thread "crea" su buzon, aunque es el mismo debido al KEY
	char* nombre_de_archivo = nombre;
   
    creaArchivo(tipoMensaje, dato, util_size, nombre_de_archivo);
    
    bool imagen_terminada = false;
    char fin; // Para saber si ya es el ultimo paquete
    while(!imagen_terminada)
    {
		buzThread->recibir(tipoMensaje); // Recibe solo mensajes de tipo tipoMensaje
		
		// Escribir en el archivo lo recibido segun la cantidad de bytes utiles
		
		fin = buzThread->miBuzon.mText[128];
		if(fin == 't'){ // Salirse si la ultima posicion es una t 
			imagen_terminada = true;
		}
		
    }
}


void archivar(char* data, int tamanoUtil) //este mae se va a encargar de ver si el tag es nuevo para ver que hace con los datos
{
    bool nuevo = true; // Decide si el tag es nuevo
    char tag = data[128]; // Estandar
    
    for (auto itr = tags.begin(); itr != tags.end(); ++itr) //revisa que no exista este tag
    { 
        
        if(tag == itr->first)
        {
            nuevo = false;
            tipoMenMap = itr->second;
        }
    } 


    if(nuevo == true)//si el tag es nuevo crea archivo*************************8
    { //OJO!!! Si el tag es nuevo, hay que crear un hilo nuevo
        // thread_queues[pos].detach()
        
        string nombre_archivo = "resultados/imagen";
        string Ccontador = to_string(contadorArchivos);
        Ccontador = nombre_archivo + Ccontador;
        char nombre[Ccontador.size()];
        strcpy (nombre, Ccontador.c_str());

        tags.insert(pair<char,int>(tag, contadorArchivos));
        buz->enviar(data, contadorArchivos, tamanoUtil); // contador lleva cuantos mensajes se han creado, 
													    // entonces los envia de ese tipo
        
        // Lanza thread nuevo
        // std::thread worker(hilo_escribir, contadorArchivos, data, tamanoUtil, nombre);
        // worker.detach();
        // el nombre del archivo es el resto del paquete
        contadorArchivos++;
        
    }   
        
    else // Si no es nuevo escribe en uno existente
    {
        // cout << "Su hilo es: "<< contadorArchivos << endl;
        buz->enviar(data, tipoMenMap, tamanoUtil); // tipoMenMap tiene la posicion por el for con iteradores del inicio
    }
}


void extraeDatos(char* datos)
{
    int tamanoUtil = 0;
    char part[3];
    memcpy(part, datos + 129, 3); // Copia los 3 chars que dan cantidad de bytes utiles
    tamanoUtil = atoi(part);
    // cout << "Size util: " << tamanoUtil << endl;
    archivar(datos, tamanoUtil);
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






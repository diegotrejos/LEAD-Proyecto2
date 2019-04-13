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

#define MAX_M 133
#define KEY_B 0xB73404
#define KEY_C 0xB60513

using namespace std;
/*typedef struct{
    char data[128];
    char tag;
    int utiles;
    char ultimo;
} bytes;*/

long tipoMenMap = 1;
Buzon* buz = new Buzon(KEY_B); // Buzon que va a guardar paquetes recibidos
Buzon* aux = new Buzon(KEY_C); // Buzon para comunicar de un hilo a otro.
map<char, long> tags; // Registra los tags con sus hilos
long contadorArchivos = 1; // Cuenta los archivos que van entrando
bool finished;
std::vector<std::thread> threads;


void creaArchivo(const char* dato, int util_size, char *nombre)//crea archivo nuevo
{
    cout << "\ncreando archivo: " << nombre << endl;
    ofstream of (nombre, ios::out | ios::binary);
    //char* c = &dato[0];
    of.write(dato, util_size);
    of.close();
}

void escribir(char* datos, int util_size, char* nombre)//continua escribiendo en archivo existente
{
   
    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

    ofstream of;  // Create Object of Ofstream
    of.open (nombre, ios::app); // Append mode

    of.write(datos, util_size);
    of.close(); // Closing the file

}

void hilo_escribir(long archivo)
{	
	cout << "ENTRE EN ESCRIBIR CON EL HILO " << archivo << endl;
    Buzon* buzThread = new Buzon(KEY_B); // Cada thread "crea" su buzon, aunque es el mismo debido al KEY
	buzThread->recibir(archivo); // Era necesario pasar el id del tipo de datos para poder recibir el mensaje
	cout << "Recibir del thread: " << buzThread->miBuzon.mText << endl;
	char part[3];
	memcpy(part, buzThread->miBuzon.mText + 129, 3);
	cout << "Part: " << part << endl;
	int bytesUtiles = atoi(part);
	cout << "Hilo datos utiles: " << bytesUtiles << endl;
    
    string nombre_archivo="resultados/imagen";
    string Ccontador=to_string(archivo); //el tipo de datos del archivo es igual al numero de archivo.
    Ccontador=nombre_archivo+Ccontador;
    char nombre[Ccontador.size()];
    strcpy (nombre, Ccontador.c_str());
   
    creaArchivo(buzThread->miBuzon.mText, bytesUtiles, nombre); //el nombre solo se crea 1 vez y no va a cambiar por hilo.
    bool imagen_terminada = false;
    int leido = 2;
    while(!imagen_terminada)
    {
		buzThread->recibir(archivo); // Recibe solo mensajes de tipo archivo
		cout << "Thread: " << archivo << " recibir: " << leido << std::endl;
		++leido;
		memcpy(part, buzThread->miBuzon.mText + 129, 3);
		bytesUtiles = atoi(part);
		cout << "Bytes utiles: " << bytesUtiles << endl;
		char fin = buzThread->miBuzon.mText[132];
		//memcpy(data, buzThread->miBuzon.mText, bytesUtiles);
		//escribir(data, bytesUtiles, nombre);
		if(fin == 't'){ // Salirse si la ultima posicion es una t 
			imagen_terminada = true;
			cout << "Imagen terminada\n";
		}
    }
}


void archivar(char* buffer) // Revisa tags
{
	
    char tag = buffer[128];
    bool nuevo=true; // Decide si el tag es nuevo
    long hilo = 0;

    
    for (auto itr = tags.begin(); itr != tags.end(); ++itr)//revisa que no exista este tag
    { 
        
        if(tag == itr->first)
        {
            nuevo =false;
            hilo=itr->second;
            //cout<<"tag: "<<tag<<" es igual a: "<<itr->first<<" que ya esta reistrado y tiene su arhcivo que se llama: "<<itr->second<<endl;;
        }
    } 


    if(nuevo==true)//si el tag es nuevo crea archivo*************************8
    {
        tags.insert(pair<char,int>(tag,contadorArchivos));
        //cout << "ENVIANDO DATO A BUZON DE HILOS" << endl;
        buz->enviar(buffer, contadorArchivos, MAX_M);
        cout << "Mandar a buzon del thread: " << buffer << endl;
        //cout << "DATO ENVIADO A BUZON DE HILOS" << endl;
        std::thread worker(hilo_escribir, contadorArchivos);
        //cout << "LUEGO DE CREAR HILO DE ESCRITURA PARA EL ARCHIVO " << contadorArchivos << endl;
        worker.detach();
        contadorArchivos++;
    }   
        
    else //si no es nuevo escribe en uno existente
    {
        buz->enviar(buffer, hilo, MAX_M);
    }
}


void extraeDatos()
{
	Buzon* buzon_arch = new Buzon(KEY_C);
	int contador = 0;
    while(true){
		//cout << "ESPERANDO A RECIBIR DATO EN EL BUZON DE ARCHIVAR" << endl;
		buzon_arch->recibir(1);
		//cout << "Arvhivar: " << contador << endl;
		//++contador;
		//cout << buzon_arch->miBuzon.mText << endl;
		cout << "Voy a archivar: " << buzon_arch->miBuzon.mText << endl;
		archivar(buzon_arch->miBuzon.mText);
    }
}

void recibe(int espera)
{
	//cout << "ENTRE EN RECIBE" << endl;
    Socket s1;  // se crea un socket de tipo SOCK_STREAM
    cout << "Ingrese el puerto por el que se comunicaran\n";
    int port = 0;
    cin >> port;
    char buffer[133];
    
    s1.Bind(port);// puerto en el que va a recibir las solicitudes
    s1.Listen( 3 );
    
    Socket* s2 = s1.Accept();// se espera una conexion
    printf("Conexion Aceptada \n");
    int contador = 0;
    while(true)
    {
		//cout << "ENVIANDO DATO AL BUZON DE ARCHIVAR" << endl;
        s2->Read(buffer, 133);
        cout << "RECEPTOR ME LLEGO: " << buffer << endl;
        cout << buffer[129] << endl;
        cout << buffer[130] << endl;
        cout << buffer[131] << endl;
        aux->enviar(buffer, 1, MAX_M);
        //cout << "DATO ENVIADO AL BUZON DE ARCHIVAR: " << contador << endl;
        ++contador;
        //archivar(buffer);
        //std::this_thread::sleep_for(std::chrono::seconds(espera));
    }
}





int main()
{
  //recibe(0);

    //thread_queues = new vector<std::queue<bytes>>();
    //thread_semaphores = new vector<Semaphore>();
    //threads = vector<std::thread>();
    //main_semaphore = new Semaphore(0,KEY);
    //delete(buz);
    //delete(aux);
    std::thread recolector(recibe, 1);
    recolector.detach();
    std::thread separador(extraeDatos);
    separador.join();
    while(!finished){

    }
    return 0;
}






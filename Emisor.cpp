#include "Emisor.h"
#include "Socket.h"
//#include "Buzon.h"
#define PORT 5050


void Emisor::creaArchivo(char tag, char* dato, int util_size)
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

void Emisor::escribir(char tag, char* datos, int util_size)//neceisto q solo con el tag pueda obtener el nombre del archivo para seguir escribiendo en el
{
	// Esto escribe el binario en una imagen
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


Emisor::Emisor()
{

}


void Emisor::envio()
{
	//sockets
	Socket s();
	cout << "Ingrese la direccion IP del servidor\n"
	string IP;
	cin >> IP;
	s.Connect( IP.c_str(), PORT );// Se realiza la conexion segun la IP de la máquina
}

void Emisor::recibe(char tag,char* paq,  int paq_size)//argumentos para que sirba buzon, v esta para pruebas, 
{
	
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
	{
		contador++;
		
		string nombre_archivo="resultados/imagen";
		string Ccontador=to_string(contador);
		Ccontador=nombre_archivo+Ccontador+".jpg";
    	char* a = new char[Ccontador.size()];
    	strcpy (a, Ccontador.c_str());

		archivos.insert(pair<char,char*>(tag,a));//el nombre del archivo es el resto del paquete

		creaArchivo(tag,paq,paq_size);
	}	
		
	else//si no es nuevo escribe en uno existente
	{
		escribir(tag,paq,paq_size);
	}

}

Emisor::~Emisor()
{
	
}

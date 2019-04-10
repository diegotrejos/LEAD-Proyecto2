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

using namespace std;
map<char,char*> archivos;//regista los archivos existentes
int contador=0;//cuenta los archivos q van entrando

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

void recibe(char tag,char* paq,  int paq_size)
{
    
    bool nuevo= true;//decide si el tag es nuevo
        
    cout<<"tag: "<< tag <<" ."<<endl;
    
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







int main()
{

//codigo q inicializa socket

while(true)
{

    //sockets retornen esos parametros para recibe
   //recibe(char tag,char* paq,  int paq_size, archivos)
}

    return 0;
}










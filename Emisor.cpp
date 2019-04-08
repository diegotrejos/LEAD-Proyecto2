#include "Emisor.h"
//#include "Buzon.h"


void Emisor::creaArchivo(char tag, char* nombre)
{
	

	string nombre_archivo;



    char* strcat(char* nombre_archivo, const char * nombre);
	ofstream ofs (nombre_archivo, ios::out | ios::binary);
	int tam = 129;
	char* c = &result[0];
    ofs.write(c, tam);
	ofs.close();

}

void Emisor::escribir(char tag, char* result)//neceisto q solo con el tag pueda obtener el nombre del archivo para seguir escribiendo en el
{
	// Esto escribe el binario en una imagen
	//ofstream ofs (nombre, ios::out | ios::binary);
	char * nombre;
	for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
	 { 
        if(tag == itr->first)
        {
        	nombre = itr->second;
        }
    } 
    string nombre_archivo;
    char* strcat(char* nombre_archivo, const char * nombre);
    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

	ofstream ofs;  // Create Object of Ofstream
    ofs.open (nombre_archivo, ios::app); // Append mode
  	int tam = 129;
	char* c = &result[0];
    ofs.write(c, tam);
    ofs.close(); // Closing the file

}


Emisor::Emisor()
{

}
/*
 Emisor::Emisor(int msqid, vector<char> v)//falta definir que va a matar esto
{
 	bool trabajando = true;
	while(trabajando == true)
		{	
			
			//Buzon buzon//creo objeto buzon;
			recibe(msqid, v);//obtengo mensaje de buzon

			//generar hilos por cada tag nuevo y ir almacenando
			// en un vector de vector<char> que cuando haya terminado se envia a ordenar.
			trabajando=false;
 		}	


}*/

void Emisor::envio()
{
	//sockets
}

void Emisor::recibe(char* paq)//argumentos para que sirba buzon, v esta para pruebas, 
{
	
	bool nuevo= true;//decide si el tag es nuevo
	
	char tag = char(paq[128]);
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
		
		

		cout<<"EL archivo se va a llama: "<<paq<<endl;
		

		archivos.insert(pair<char,char*>(tag,paq));//el nombre del archivo es el resto del paquete

		creaArchivo(tag, paq);

	}	
	else//si no es nuevo escribe en uno existente
	{
	escribir(tag,paq);
	
	}	

}




Emisor::~Emisor()
{
	
}

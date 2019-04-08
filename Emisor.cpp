#include "Emisor.h"
//#include "Buzon.h"


void Emisor::creaArchivo(char tag, char* dato)
{

char* nombre;	
	for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
	 { 
        if(tag == itr->first)
        {
        	nombre = itr->second;
        }
    }

	
	string nombre_archivo="resultados/";
    char* a = new char[nombre_archivo.size()];
    strcpy (a, nombre_archivo.c_str());
    strcat (a, nombre);

	cout<<"creando archivo "<< a <<endl;
	ofstream ofs (a, ios::out | ios::binary);
	int tam = 129;
	char* c = &dato[0];
    ofs.write(c, tam);
	ofs.close();

}

void Emisor::escribir(char tag, char* result)//neceisto q solo con el tag pueda obtener el nombre del archivo para seguir escribiendo en el
{
	// Esto escribe el binario en una imagen
	//ofstream ofs (nombre, ios::out | ios::binary);
	cout<<"continua escribiendo"<<endl;
	char * nombre;
	for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
	 { 
        if(tag == itr->first)
        {
        	nombre = itr->second;
        }
    } 
   
	string nombre_archivo="resultados/";
    char* a = new char[nombre_archivo.size()];
    strcpy (a, nombre_archivo.c_str());
    strcat (a, nombre);

    //cout<<"se va a escribir en el archivo ya existente llamado: "<<nombre_archivo<<endl;

	ofstream ofs;  // Create Object of Ofstream
    ofs.open (a, ios::app); // Append mode
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
		
		archivos.insert(pair<char,char*>(tag,"Auxilio"));//el nombre del archivo es el resto del paquete

		/*
		srand(time(NULL));
		int nombre;
		nombre=rand()%127;
  		cout<<"EL archivo se va a llama: "<<endl;
		*/
		creaArchivo(tag,paq);
	}	
		
	else//si no es nuevo escribe en uno existente
	{
	escribir(tag,paq);
	
	}	

}




Emisor::~Emisor()
{
	
}

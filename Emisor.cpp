#include "Emisor.h"
//#include "Buzon.h"



void Emisor::creaArchivo(char tag, char* nombre)
{
	// Esto escribe el binario en una imagen
	ofstream ofs (nombre, ios::out | ios::binary);
	ofs.close();

}

void Emisor::escribir(char tag, vector<char> result)//neceisto q solo con el tag pueda obtener el nombre del archivo para seguir escribiendo en el
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

	ofstream ofs;  // Create Object of Ofstream
    ofs.open (nombre, ios::app); // Append mode
  	int tam = result.size();
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


void Emisor::recibe(vector<char> v)//argumentos para que sirba buzon, v esta para pruebas, 
{
	bool nuevo= true;//decide si el tag es nuevo
	

	char tag = v[129];
	v.erase(v.end());//borra el tag
	for (auto itr = archivos.begin(); itr != archivos.end(); ++itr)//revisa que no exista este tag
	 { 
        if(tag == itr->first)
        {
        	nuevo =false;
        }
    } 


	if(nuevo ==true)//si el tag es nuevo crea archivo
	{
		
		archivos.insert(pair<char,char*>(tag,v.data()));//el nombre del archivo es el resto del paquete
		creaArchivo(tag, v.data());

	}	
	else//si no es nuevo escribe en uno existente
	{
	escribir(tag,v);
	
	}	

}




Emisor::~Emisor()
{
	
}

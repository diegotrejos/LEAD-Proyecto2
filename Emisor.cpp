#include "Emisor.h"



//void Emisor::creaArchivo(char* nombre)
//{
	// Esto escribe el binario en una imagen
//}

void Emisor::escribir(char tag)//neceisto q solo con el tag pueda obtener el nombre del archivo para seguir escribiendo en el
{
	int size = 0;
	char * nombre;
	for (auto itr = archivos.begin(); itr != archivos.end(); ++itr){//revisa que no exista este tag
        if(tag == itr->first){
        	nombre = itr->second;
        }
    }

	ofstream ofs;  // Create Object of Ofstream
    ofs.open (nombre, ios::app); // Append mode
  	bzn->recibir();
	size = bzn->miBuzon.mensajeUtil;
	ofs.write(bzn->miBuzon.mText, size);
    ofs.close(); // Closing the file

}



Emisor::Emisor(Buzon* miBuzon) : contador(1)
{
	bzn = miBuzon;
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


void Emisor::recibe()//argumentos para que sirba buzon, v esta para pruebas, 
{
	while(true){
		bool nuevo = true;//decide si el tag es nuevo
		
		int size = 0;
		char * nombre;
		bzn->recibir();
		char tag = bzn->miBuzon.tag;
		for (auto itr = archivos.begin(); itr != archivos.end(); ++itr){//revisa que no exista este tag 
			if(tag == itr->first){
				nuevo =false;
			}
		}
		
		if(nuevo ==true)//si el tag es nuevo crea archivo
		{
			sprintf(nombre, "resultados/imagen%d.jpg", contador++);
			archivos.insert(pair<char,char*>(tag, nombre));//el nombre del archivo es el resto del paquete
			ofstream ofs (nombre, ios::out | ios::binary);
			ofs.close();
		}
		
		//for (auto itr = archivos.begin(); itr != archivos.end(); ++itr){//revisa que no exista este tag
		//	if(tag == itr->first){
		//		nombre = itr->second;
		//	}
		//}
		
		ofstream ofs;  // Create Object of Ofstream
		ofs.open (nombre, ios::out | ios::binary | ios::app); // Append mode
		size = bzn->miBuzon.mensajeUtil;
		ofs.write(bzn->miBuzon.mText, size);
		ofs.close(); // Closing the file
	}
}




Emisor::~Emisor()
{
	
}

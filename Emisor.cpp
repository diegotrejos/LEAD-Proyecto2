#include "Emisor.h"
//#include "Buzon.h"


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
	//ofstream ofs (nombre, ios::out | ios::binary);
	//cout<<"continua escribiendo"<<endl;
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
//	char* c = &result[0];
    of.write(datos, tam);
    of.close(); // Closing the file

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

void Emisor::recibe(char tag,char* paq,  int paq_size)//argumentos para que sirba buzon, v esta para pruebas, 
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

		/*
		srand(time(NULL));
		int nombre;
		nombre=rand()%127;
  		cout<<"EL archivo se va a llama: "<<endl;
		*/
		creaArchivo(tag,paq,paq_size);
	}	
		
	else//si no es nuevo escribe en uno existente
	{

	escribir(tag,paq,paq_size);
	
	}
	//contador++;
	//cout<<"Termine paquete#"<<contador<<endl;	

}




Emisor::~Emisor()
{
	
}

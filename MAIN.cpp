
#include <algorithm>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Emisor.h"
#include "Semaphore.h"
#include "Buzon.h"

#define KEY 0xB57414

using namespace std;

Semaphore* contrat_ctrl; //semaforo para controlar la cantidad de contratistas
Buzon* bzn;


// g++ -Wall -Wextra Buzon.h Buzon.cpp Semaphore.cpp Semaphore.h Emisor.cpp Emisor.h MAIN.cpp -o prueba
// PARA CORRERLO: ./prueba imagenes/



int filter_function(const struct dirent *dir){
	if(((strstr(dir->d_name, ".png") || strstr(dir->d_name, ".jpg")) || ((strstr(dir->d_name, ".jpeg")) || (strstr(dir->d_name, ".gif")))) || ((strstr(dir->d_name, ".JPEG")))){
		return 1;
	} else{
		return 0;
	}
}

bool test_directory(char* directorio){
	DIR* work_bench = opendir(directorio);
	if(!work_bench){
		return false;
	} else{
		closedir(work_bench);
		return true;
	}
}


void contratista(char const* imagen, const char tag)
{	
	cout << imagen << " " << tag << endl;
	ifstream ifs(imagen, ios::binary|ios::ate); //lee la imagen en bytes
	ifstream::pos_type tam = ifs.tellg(); //saca el tamano 

	vector<char> result(512); // crea vector de 512 bytes

	ifs.seekg(0, ios::beg);

	int contador = 0;
	int cantidadMensajes = 0;
	bzn->miBuzon.tag = tag;
	while(contador+512 < int(tam)){
		cout << "EL CONTADOR ES: " << contador << " Y EL TAM ES: " << int(tam) << endl;
		ifs.read(&result[0], 512);
		if(ifs){
			//cout << "LEI BIEN LOS DATOS" << endl;
		}
		contador = contador + 512;
		
		vector<char> vector1(result.begin(), result.begin() + 128);
		bzn->enviar(vector1.data(), 1, 128);
		++cantidadMensajes;
		
		vector<char> vector2(result.begin() + 128, result.begin() + 256); 
		bzn->enviar(vector2.data(), 1, 128);
		++cantidadMensajes;
		
		vector<char> vector3(result.begin() + 256, result.begin() + 384); 
		bzn->enviar(vector3.data(), 1, 128);
		++cantidadMensajes;
		
		vector<char> vector4(result.begin() + 384, result.begin() + 512);
		bzn->enviar(vector4.data(), 1, 128);
		++cantidadMensajes;
	}
	while (contador != int(tam)){ //cuando queda menos de 512 bytes
		if((int(tam) - contador) > 127){
			result.resize(128);
			ifs.read(&result[0], 128);
			if(ifs){
				//cout << "LEI BIEN LOS DATOS" << endl;
			}
			contador  = contador + 128;
			//result.insert(result.end(), tag);
			bzn->enviar(result.data(), 1, 128);
			++cantidadMensajes;
		}else{
			result.resize(int(tam)-contador);
			int size = int(tam)-contador;
			ifs.read(&result[0], size);
			if(ifs){
				cout << "LEI BIEN LOS DATOS2" << endl;
			}
			contador  = tam;
			//result.insert(result.end(), tag);
			bzn->enviar(result.data(), 1, size);
			++cantidadMensajes;
		}
	}
	printf("Cantidad de mensajes enviados: %d\n", cantidadMensajes);
	
	contrat_ctrl->notify();
	exit(0);
}

int lector(char* directorio){
	if(!test_directory(directorio)){ // Revisa si el posible abrir el directorio
		std:: cout << "Fallo al abrir el directorio\n";
		return 1;
	}
	
	struct dirent** imagenes; // Estructura que guarda la posicion de memoria y el nombre de las imagenes
	int n,i;
	n = scandir(directorio, &imagenes, filter_function, versionsort);
	if (n < 0)
        perror("scandir");
    else
    {
		cout << n << endl;
        for(i =0 ; i < 1; ++i)
        {
			contrat_ctrl->wait();
			cout << i << endl;
			if(fork() == 0){
				contratista(strcat(directorio, imagenes[i]->d_name), char(i+33));
				free(imagenes[i]);
            }
        }
        free(imagenes);
    }
	return 0;
}








int main(int argc, char* argv[]){
	if(argc < 2){
		cout << "Es necesario indicar el directorio" << endl;
		return(1);
	}
	map<char,char*> archivos;//podria hacer mapas, tengo tag y nombre de archivo
	int contador = 1;
    if(fork() == 0){ //Lector
		//contenido de lector.
		char* directorio;
		directorio = argv[1];
		//cout << "antes de crear semaforo" << endl;
		contrat_ctrl = new Semaphore(2, KEY);
		//cout << "después de crear semaforo" << endl;
		bzn = new Buzon(KEY);

		int success = lector(directorio);
		/*if(success != 0){
			free(contrat_ctrl);
			free(bzn);
			return 1;
		}
		free(bzn);
		free(contrat_ctrl);*/
	 } else{ //Emisor
		cout << "ARRANCÓ EL EMISOR" << endl; 
		//Emisor* emi = new Emisor(bzn);
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
		cout << "CERRÓ EL EMISOR" << endl; 
	}
	
	
	return 0;
}









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


// g++ -Wall -Wextra Buzon.h Buzon.cpp Semaphore.cpp Semaphore.h MAIN.cpp -o prueba
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
	
cout<<"Se empieza a envia la imagen: "<< imagen <<"con tag: "<< tag<<endl;
	
	Emisor* emi = new Emisor;
	

	ifstream ifs(imagen, ios::binary|ios::ate); //lee la imagen en bytes
	ifstream::pos_type tam = ifs.tellg(); //saca el tamano 

	vector<char> result(512); // crea vector de 512 bytes
	//char* result;
	ifs.seekg(0, ios::beg);

	int contador = 0;
	while(contador+512 < int(tam)){
		//cout << "EL CONTADOR ES: " << contador << " Y EL TAM ES: " << int(tam) << endl;
		ifs.read(&result[0], 512);
		if(ifs){
		//	cout << "LEI BIEN LOS DATOS" << endl;
		}
		contador = contador + 512;
		
	//	cout << "VOY A INSERTAR LOS DATOS 1" << endl;
		vector<char> vector1(result.begin(), result.begin() + 128);
		vector1.insert( vector1.end(), tag );
	//	cout << "VOY A ENVIAR LOS DATOS 1" << endl;
		emi->recibe(vector1.data());
	//	cout<<"flag1";	
		//bzn->enviar(vector1.data());
		
	//	cout << "VOY A INSERTAR LOS DATOS 2" << endl;
		vector<char> vector2(result.begin() + 128, result.begin() + 256); 
		vector2.insert( vector2.end(), tag );
	//	cout << "VOY A ENVIAR LOS DATOS 2" << endl;
		emi->recibe(vector2.data());
		//bzn->enviar(vector2.data());
		
	//	cout << "VOY A INSERTAR LOS DATOS 3" << endl;
		vector<char> vector3(result.begin() + 256, result.begin() + 384); 
		vector3.insert( vector3.end(), tag );
	//	cout << "VOY A ENVIAR LOS DATOS 3" << endl;
		//bzn->enviar(vector3.data());
		emi->recibe(vector3.data());
		
	//	cout << "VOY A INSERTAR LOS DATOS 4" << endl;
		vector<char> vector4(result.begin() + 384, result.begin() + 512);
		vector4.insert( vector4.end(), tag );
	//	cout << "VOY A ENVIAR LOS DATOS 4" << endl;
		//bzn->enviar(vector4.data());
		emi->recibe(vector4.data());
	}
	while (contador != int(tam)){ //cuando queda menos de 512 bytes
		if((int(tam) - contador) > 127){
			result.resize(128);
			ifs.read(&result[0], 128);
			if(ifs){
		//		cout << "LEI BIEN LOS DATOS" << endl;
			}
			contador  = contador + 128;
			result.insert(result.end(), tag);
			emi->recibe(result.data());
			//bzn->enviar(result.data());
		}else{
			result.resize(int(tam)-contador);
			ifs.read(&result[0], (int(tam)-contador));
			if(ifs){
		//		cout << "LEI BIEN LOS DATOS" << endl;
			}
			contador  = tam;
			result.insert(result.end(), tag);
			emi->recibe(result.data());
			//bzn->enviar(result.data());
		}
	}
	
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
				//printf("%ld %s\n",imagenes[i]->d_ino, imagenes[i]->d_name);
				contratista(strcat(directorio, imagenes[i]->d_name), char(i+33));
				free(imagenes[i]);
            }
        }
        free(imagenes);
    }
	return 0;
}



int main(int argc, char* argv[]){

	char letra = '!';
    	
	cout<<"prueba con imagen prueba1.jpg con tag: "<< letra <<endl;
	contratista("prueba2.jpg", letra);
	if( letra = '}'){
		letra = '!';
	}else{
		letra  = static_cast<char>(letra + 1);
	}
	

/*	if(argc < 2){
		cout << "Es necesario indicar el directorio" << endl;
		return(1);
	}
*/	
	
	


   //Emisor
	/*
	Emisor* emi = new Emisor;
	Buzon* buzon_emisor = new Buzon(1, KEY);
	bool trabajando = true;
	//while(trabajando == true)
	//	{	
					
			//buzon q no logre usar  que retorn el veector<char> imagen
			//buzon_emisor->recibir();
			//buzon_emisor->msgbuf.mText;
			
			

			//emi->recibir(buzon_emisor->buzonMensajes.mText);

			//trabajando=false;//algo para frenarlo hay q definir eso
 	//	}	
	 */
	
	
/*	//contenido de lector.
	char* directorio;
	directorio = argv[1];
	//cout << "antes de crear semaforo" << endl;
	contrat_ctrl = new Semaphore(2, KEY);
	//cout << "después de crear semaforo" << endl;
	bzn = new Buzon(1, KEY);

	int success = lector(directorio);
	/*if(success != 0){
		free(contrat_ctrl);
		free(bzn);
		return 1;
	}
	free(bzn);
	free(contrat_ctrl);*/
	return 0;
}

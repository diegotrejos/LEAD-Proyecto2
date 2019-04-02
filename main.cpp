#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <vector>

bool test_directory(char* directorio){
	DIR* work_bench = opendir(directorio);
	if(!work_bench){
		return false;
	} else{
		closedir(work_bench);
		return true;
	}
}


int filter_function(const struct dirent *dir){
	if(((strstr(dir->d_name, ".png") || strstr(dir->d_name, ".jpg")) || ((strstr(dir->d_name, ".jpeg")) || (strstr(dir->d_name, ".gif")))) || ((strstr(dir->d_name, ".JPEG")))){
		return 1;
	} else{
		return 0;
	}
}

int lector(const char* directorio){
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
        for(i =0 ; i < n; ++i)
        {
            printf("%ld %s\n",imagenes[i]->d_ino, imagenes[i]->d_name);
            free(imagenes[i]);
        }
        free(imagenes);
    }
    
    // Crear contratistas y seguir contratando hasta que no hayan mas imagenes por analizar
	return 0;
}


std::vector<char> leerBytes(char const* imagen)
{
	// Esto lee toda la imagen
	ifstream ifs(imagen, ios::binary|ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	std::vector<char> result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
}



int main(int argc, char* argv[]){
	// Se pasa el directorio con las imagenes como argumento del programa
	if(argc != 2){ // Revisa si pasaron la carpeta como argumento del programa
		return std::cerr << "Para utilizar el programa de manera correcta debe ingresar la carpeta con las imagenes como argumento del programa\n";
	}
	
	lector(argv[1]);
    return 0;
}

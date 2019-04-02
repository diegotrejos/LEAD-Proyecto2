#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <string.h>
#include <iterator>

using namespace std;

vector<char> leerBytes(char const* imagen)
{
	// Esto lee toda la imagen
	ifstream ifs(imagen, ios::binary|ios::ate); //lee la imagen en bytes
	ifstream::pos_type tam = ifs.tellg(); //saca el tamano 

	vector<char> result(512); // crea vector de 512 bytes
	vector<char> pruebaVec; //para pruebas (se insertan todos los paquetes para ver si hacen bien )

	ifs.seekg(0, ios::beg);

	int contador = 0;
	while(contador+512 < tam){
		ifs.read(&result[0], 512);
		contador = contador + 512;
		vector<char> vector1(result.begin(), result.begin() + 128); 
		pruebaVec.insert( pruebaVec.end(), vector1.begin(), vector1.end() );
		vector<char> vector2(result.begin() + 128, result.begin() + 256); 
		pruebaVec.insert( pruebaVec.end(), vector2.begin(), vector2.end() );
		vector<char> vector3(result.begin() + 256, result.begin() + 384); 
		pruebaVec.insert( pruebaVec.end(), vector3.begin(), vector3.end() );
		vector<char> vector4(result.begin() + 384, result.begin() + 512); 
		pruebaVec.insert( pruebaVec.end(), vector4.begin(), vector4.end() );
		//mandar los 4 vectores por el buzon al emisor
	}	
	while (contador != tam){ //cuando queda menos de 512 bytes
		if((tam - contador) > 127){
			result.resize(128);
			ifs.read(&result[0], 128);
			pruebaVec.insert( pruebaVec.end(), result.begin(), result.end() );
			contador  = contador + 128;
			//mandar result por el buzon
		}else{
			result.resize(tam-contador);
			ifs.read(&result[0], (tam-contador));
			pruebaVec.insert( pruebaVec.end(), result.begin(), result.end() );
			contador  = tam;
			//mandar result por el buzon
		}
	}
	
	//hay que mandar nombre del archivo por el buzon para poder recontruir la imagen
	return pruebaVec;
}

void escribir(vector<char> result)
{
	// Esto escribe el binario en una imagen
	ofstream ofs ("nuevaImagen2s.jpeg", ios::out | ios::binary);
	int tam = result.size();
	char* c = &result[0];
    ofs.write(c, tam);
	ofs.close();

}

main(){

	vector<char> v = leerBytes("index.jpeg");
	cout << "tamMain: " << v.size() << endl;
	escribir(v);

	return 0;
}

#include "Buzon.h"
#include <iostream>
int main(){
	Buzon* buzon = new Buzon(1, 0xB57414);
	std::cout << "Esperando mensaje ... \n";
	std::cout << buzon->miBuzon.mText;
	buzon->recibir();
	free(buzon);
}

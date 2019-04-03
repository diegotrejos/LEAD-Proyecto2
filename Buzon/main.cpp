#include "Buzon.h"

int main(){
	Buzon* buzon1 = new Buzon(1, 0xB7304);
	char mensaje[128] = "Hola mensaje";
	buzon1->enviar(mensaje);
	sleep(10);
	buzon1->sacarQueue();
}

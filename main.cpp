#include <iostream>
#include "Lector.h"


int main()
{

int cnt=0;
Lector lec;
for(int i =0; i<2; i++)
{
	
if(cnt == 0)
{	
lec.contrat("prueba1.jpg",cnt);
//string q se guarda aqui no sirve cuando llega al metodo
}
else if(cnt == 1)
{
lec.contrat("prueba2.jpg",cnt);
}


}
	return 0;
}
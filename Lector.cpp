#include "Lector.h"


Lector::Lector()
{
	std::cout<<"creo objeto"<<std::endl;
}

void Lector::contrat(std::string addrs, int num)
{

   cout<<"Soy Contrat #"<< num;

    int counter = 0;
    pid_t pid = fork();

    if (pid == 0)
    {
       //aqui poner ciclo que obtiene bytes y envia bytes
      for(int i=0; i<50; i++)
      {
      	cout<<addrs;
       
      }
      //aqui enviar a lector q murio este mae
      cout<<"termine";
    }
 
}
Lector::~Lector()
{

}
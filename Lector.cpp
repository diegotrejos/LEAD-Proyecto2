#include "Lector.h"


Lector::Lector()
{
	std::cout<<"creo objeto"<<std::endl;
}

struct std::vector<char> leerBytes(char const* filename)//codigo pra extraer bytes
{

      ifstream ifs(filename, ios::binary|ios::ate);
      ifstream::pos_type pos = ifs.tellg();
      
  std::vector<char>  result(pos);
      
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

      return result;
}


void Lector::contrat(std::string addrs, int num)
{

   cout<<"Soy Contrat #"<< num;

    int counter = 0;
    pid_t pid = fork();

    if (pid == 0)
    {
       
      	
//el string addrs da error 
    vector<char> vec = leerBytes("prueba1.jpg");//obtiene bytes

    cout << "total bytes: " << vec.size() << endl;
    printf("\\Hex: %.2x", vec[1]);
    cout << endl;
    printf("Decimal : %d ", vec[1]);
    cout << endl;
 //aqui enviar a lector q murio este mae

     
      cout<<"termine soy:"<<num;
    }
 
}




Lector::~Lector()
{

}
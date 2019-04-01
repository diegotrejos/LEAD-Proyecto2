#include <fstream>
#include <vector>
#inlude <iostream>
class Lector
{

public:
Contratista()
{
	std::cout<<"Nacio contratista";
}

std::vector<char> leerBytes(char const* filename)
{

      ifstream ifs(filename, ios::binary|ios::ate);
      ifstream::pos_type pos = ifs.tellg();
      
  std::vector<char>  result(pos);
      
    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

      return result;
}
~Contratista();
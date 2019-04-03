#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static vector<char> leerBytes(char const* filename);

int main(){

    	vector<char> vec = leerBytes("/home/adavidovich08/Downloads/Logo-UCR.jpg");

	cout << "total bytes: " << vec.size() << endl;
	printf("\\Hex: %.2x", vec[1]);
	cout << endl;
	printf("Decimal : %d ", vec[1]);
	cout << endl;
	
   	return 0;
}

static vector<char> leerBytes(char const* filename){

    	ifstream ifs(filename, ios::binary|ios::ate);
    	ifstream::pos_type pos = ifs.tellg();
    	
	std::vector<char>  result(pos);
   		
	ifs.seekg(0, ios::beg);
   	ifs.read(&result[0], pos);

    	return result;
}



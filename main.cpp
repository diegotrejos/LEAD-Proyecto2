#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

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

int main(int argc, char* argv[]){
	char* directorio = argv[1];
	if(!test_directory(directorio)){
		std:: cout << "failed to open directory\n";
		return 1;
	}
	struct dirent **namelist;
	int n,i;
	n = scandir(directorio, &namelist, filter_function, versionsort);
	if (n < 0)
        perror("scandir");
    else
    {
        for(i =0 ; i < n; ++i)
        {
            printf("%ld %s\n",namelist[i]->d_ino, namelist[i]->d_name);
            free(namelist[i]);
        }
        free(namelist);
    }
    
    
    
    
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

    
    
    
    return 0;
}

///home/radamantis/Pictures

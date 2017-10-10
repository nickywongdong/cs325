#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
using namespace std;
unsigned char isFile = 0x8;	//File type returned by dirent class


int main()	//assuming Im only getting the path to the directory of the files
{
	string path = "/nfs/stak/users/dorichp/Practice325/1/";	//Ex. Directory Path
	const char * c = path.c_str();	
	const char * temp;			
	DIR *dir;
	FILE *fd;
	struct dirent *ent;
	string fd_full;

	//1 <= m <= 10
	FILE *file_pointers[9];	//should be dynamic eventually
	int n = 0;	

	if((dir = opendir (c)) != NULL)
	{
		while(( ent = readdir (dir)) != NULL) 
		{
			if(ent->d_type == isFile)		//excludes ".", ". ."
			{	
				string str(ent->d_name);	//char*[]->string
				fd_full = path + str;		//full path
				temp = fd_full.c_str();		//string-> const char*
				fd = fopen(temp, "wr"); //opens file to get file desc.
				printf("%s\n " , ent->d_name);
				file_pointers[n] = fd;	//adds file pointer to array
				n++;
			}
				
		}
		//all files are open, file descriptors stored in the array
		for(int i = 0; i < n; i++)
		{

			//file access via array:
			fprintf(file_pointers[i], "TESTING FILE ACCESS");	
			fclose(file_pointers[i]);
		}
	
		closedir(dir);
	} 
	else 
	{
	//couldn't open directory 
	printf("Error, couldn't open file");
	return 1;
	}

	return 0;
}

	








#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <sys/types.h>

#include <dirent.h>

#include <unistd.h>

#define SIZE 256

int getOrderNum(char* name);



void main(int argc, char* argv[])

{

	if (argc != 2) { printf("Wrong number of arguments!\n"); exit(1); }

	printf("%d Orders\n", getOrderNum(argv[1]));

}
int getOrderNum(char* name) {

	char path[SIZE]; //path will contain the path of the dir.

	DIR* dir; //will help us to recognize the dirs.

	int count = 0; //number of orders

	struct dirent* readdr;

	strcpy(path, name);

	strcat(path, "_Order");

	if ((dir = opendir(path)) == NULL) {

		perror("opendir");

		exit(1);

	}
	while ((readdr = readdir(dir)) != NULL) {

		count++;

	}

	closedir(dir);

	return count - 2; //returning the number of file minus the path of /home/braude and the dir of the resturant.





}



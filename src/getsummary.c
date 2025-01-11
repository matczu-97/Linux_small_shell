
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#define BUF 200


void main(int argc, char* argv[]) {
	int id;
	int from;
	int rbytes;
	char* token;
	char buffer[BUF] = { 0 };
	id = fork();
	if (id == 0) {
		execv("GetNumComp", NULL);
		perror("problem");
		exit(1);
	}
	wait();
	from = open("Black_Friday/camp_partic.txt", O_RDONLY);
	if (from == -1) { perror("open"); exit(1); }
	if ((rbytes = read(from, &buffer, BUF)) == -1) //read from file
	{
		perror("read"); exit(1);
	}

	token = strtok(buffer, "\n");
	while (token != NULL) {

		//get count of files in folder named token_orders
		if ((id = fork()) == 0) {
			execl("GetOrderNum", "GetOrderNum", token, (char*)0);
			if (errno) {
				printf("Error!\n");
				exit(1);
			}
		}
		waitpid(id);
		token = strtok(NULL, "\n");

	}

	close(from);
	exit(0);
}








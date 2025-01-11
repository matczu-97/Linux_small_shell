#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 200

void main(int argc, char* argv[]) {
	if (argc > 1) {
		printf("ERROR"); exit(1);
	}s
	int rbytes;
	char* token;
	int lines = 0;
	char buffer[BUF_SIZE];
	int from;
	from = open("Black_Friday/camp_partic.txt", O_RDONLY);
	if (from == -1) { perror("open"); exit(1); }
	if ((rbytes = read(from, &buffer, BUF_SIZE)) == -1) //read from file
	{
		perror("read"); exit(1);
	}
	token = strtok(buffer, "\n");
	while (token != NULL) {
		lines++;
		token = strtok(NULL, "\n");
	}
	printf("%d companies\n", lines);
	close(from);
	exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUF_SIZE 200

void main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("ERROR");
		exit(1);
	}

	int t_file;
	char folderName[BUF_SIZE] = { 0 };
	int pid;

	strcat(folderName, argv[1]);
	strcat(folderName, "_Order");
	t_file = open(folderName, O_RDONLY);
	if (t_file == -1) { write(0, "Company Not Found!\n", strlen("Company Not Found!\n")); close(t_file); exit(1); }

	write(0, "Orders in ", strlen("Orders in "));
	write(0, argv[1], strlen(argv[1]));
	write(0, " ---- ", strlen(" ---- "));
	if (fork() == 0) {
		execl("/bin/bash", "bash", "countFiles.sh", folderName, NULL);  //executing bash to run shell file that counts files in directory
		if (errno) {
			printf("error\n");
			exit(1);
		}
	}
	waitpid(pid);
	exit(0);

}

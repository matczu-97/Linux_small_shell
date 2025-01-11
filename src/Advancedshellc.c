#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

void main(int argc, char* argv[]) {
	int id, rbytes, count = 0, j;
	char* arr[3];
	char path[20] = { "/bin/" };
	const char s[2] = " ";
	char* counter;
	char action[100];
	if (argc != 1) {
		printf("ERROR");
		exit(1);
	}
	mkdir("Black_Friday", 0777);
	int newFile = open("Black_Friday/camp_partic.txt", O_RDWR | O_CREAT, 0644);
	if (newFile == -1) { perror("open1"); exit(1); }
	close(newFile);
	write(0, "AdvShell>", 9);
	for (j = 0; j < 3; j++) {
		arr[j] = NULL;
	}

	while (1) {

		if ((rbytes = read(0, &action, 100)) == -1) {
			perror("read");
			exit(1);
		}
		counter = strtok(action, "\n");
		counter = strtok(action, s);
		if (strcmp(counter, "exit") == 0) {
			while (wait(NULL) > 0);
			//execl("
			printf("END");
			exit(0);
		}

		while (counter != NULL) {
			arr[count] = counter;
			count++;
			counter = strtok(NULL, s);
		}

		if ((id = fork()) == -1) {
			perror("fork() failed.");
			exit(EXIT_FAILURE);
		}

		if (id == 0) {
			strcat(path, arr[0]);
			//execl(path,arr[0],arr[1],arr[2],arr[3],NULL);
			execv(path, arr);
			if (errno) { //if there was an error
				execv(arr[0], arr);
				if (errno) {
					perror(" ");
					printf("Not supported\n");
					exit(1);
				}
			}

		}
		wait(NULL);
		for (j = 0; j < 3; j++) {
			arr[j] = NULL;
		}
		write(0, "AdvShell>", 9);
		count = 0;
	}

}

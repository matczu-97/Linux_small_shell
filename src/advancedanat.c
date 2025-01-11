#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#define BUF_SIZE 200


void main(int argc, char* argv[])
{
	if (argc != 1) {
		printf("ERROR");
		exit(1);
	}
	int rbytes;
	char buffer[BUF_SIZE];
	char path_f[BUF_SIZE] = "/bin/"; //the path for the commands should start from bin
	char* delimeters = " \t\r\n"; //used to remove any unnecessary characters from the input
	char* token;
	char* arguments[4];
	int length = 0;
	int child_pid, status;

	mkdir("Black_Friday", 0777);
	int newFile = open("Black_Friday/camp_partic.txt", O_RDWR | O_CREAT, 0644);
	if (newFile == -1) { perror("open1"); exit(1); }
	close(newFile);

	while (strcmp(buffer, "exit") != 0) { //while the user input is not "exit"
		printf("AdvShell>");
		fflush(NULL); //flush the stream with unwritten data to allow correctly working input
		memset(buffer, 0, sizeof(buffer)); //clear the buffer
		if ((rbytes = read(0, &buffer, BUF_SIZE)) == -1) //read from stdin
		{
			perror("read"); exit(1);
		}

		token = strtok(buffer, delimeters); //remove unnecessary characters
		length = 0;
		while (token != NULL) {
			arguments[length] = token;
			length++;
			token = strtok(NULL, delimeters);
		}
		arguments[length] = NULL;
		strcpy(path_f, "/bin/\0"); //refresh the path of the commands
		strcat(path_f, arguments[0]); //add the command from the user to the path
		if (strcmp(buffer, "exit") != 0) { //execute only if the command was not "exit"
			if ((child_pid = fork()) == 0) {
				execvp(path_f, arguments);
				if (errno) { //if there was an error
					execv(arguments[0], arguments);
					if (errno) {
						perror(" ");
						printf("Not Supported\n");
						exit(1);
					}
				}
			}
			else if (child_pid > 0) {
				do {
					waitpid(child_pid, &status, 0);
				} while (!WIFEXITED(status));//wait until the child process terminated normally
			}
			else {
				if (errno) {
					printf("ERROR ERROR ERROR\n");
					exit(1);
				}
			}
		}
	}
	printf("END\n");
}


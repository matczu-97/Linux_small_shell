#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	int id;

	id = fork();
	if (id == 0) {
		execl("/bin/rm", "rm", "Black_Friday/camp_partic.txt", NULL);
	}
	wait();
	rmdir("Black_Friday");
	printf("END\n");
	exit(0);
}
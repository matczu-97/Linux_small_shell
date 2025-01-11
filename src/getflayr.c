
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
	int from, rbytes;
	char buffer[250];
	char to_read[200];
	sprintf(to_read, "%s.txt", argv[1]);
	if ((from = open(to_read, O_RDONLY)) == -1) {
		perror("open"); exit(1);
	}
	if ((rbytes = read(from, &buffer, 300)) == -1) {
		perror("read"); exit(1);
	}
	while (rbytes > 0) {
		printf("%s", buffer);
		rbytes = read(from, &buffer, 300);
	}
	close(from);
	exit(0);
}

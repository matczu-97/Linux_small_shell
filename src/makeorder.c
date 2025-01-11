
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
	if (argc != 3) { perror("Wrong number of arguments\n"); exit(1); }
	int fd, to;
	int rbytes;
	float discount;
	int quan;
	float total = 0;
	char action[BUF];
	char dirname[BUF] = { 0 };
	char pricefile[BUF];
	char name2[20] = { "" };
	char* p;
	char* place;
	int pid;
	char buffer[BUF] = { 0 };
	char temp[20] = { "" };
	char p_buffer[BUF] = { 0 };
	int status;


	if ((pid = fork()) == 0) {
		execl("GetFlayer", "GetFlayer", argv[1], (char*)0);
		if (errno) {
			printf("Company Not Found!\n");
			exit(1);
		}
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0) {
		exit(1);
	}
	strcat(dirname, argv[1]);
	strcat(dirname, "_Order/");
	strcat(dirname, argv[2]);
	strcat(dirname, ".txt");
	to = open(dirname, O_WRONLY | O_CREAT, 0644);
	if (to == -1) { perror("open12"); exit(1); }
	write(to, argv[1], strlen(argv[1]));
	write(to, " Order\n", strlen(" Order\n"));


	sprintf(pricefile, "%s.txt", argv[1]);
	fd = open(pricefile, O_RDONLY);
	if (fd == -1) { perror("open2"); exit(1); }
	if ((rbytes = read(fd, p_buffer, BUF)) == -1)
	{
		perror("read"); exit(1);
	}
	close(fd);
	p = p_buffer;
	while (*p != '\n') {
		p++;
	}
	discount = atoi(p);

	write(0, "insert your choice:(STOP to finish)\n", strlen("insert your choice:(STOP to finish)\n"));
	if ((rbytes = read(0, buffer, BUF)) == -1) { perror("read"); exit(1); }

	while (strcmp(buffer, "STOP\n") != 0) {

		if (strcmp(buffer, "STOP\n") != 0) {
			quan = atoi(strrchr(buffer, ' '));
			p = strrchr(buffer, ' ');
			strncpy(name2, buffer, strlen(buffer) - strlen(p));
			name2[strlen(buffer) - strlen(p)] = '\0';
			place = strstr(p_buffer, name2);
			if (place == NULL) { printf("no item"); continue; }
			place = strstr(place, "NIS");
			place = place - 3;
			while (1) {
				if (*place == '.')break;
				place--;
			}
			place++;
			total += (atoi(place) * quan);
			write(to, name2, strlen(name2));
			memset(name2, '\0', 20);
			sprintf(name2, " %d\n", quan);
			write(to, name2, strlen(name2));
			memset(name2, '\0', 20);
			memset(buffer, 0, sizeof(buffer));
			if ((rbytes = read(0, &buffer, BUF)) == -1) { perror("read"); exit(1); }
		}
	}
	memset(name2, '\0', 20);
	sprintf(name2, "%.2f", total * ((float)(100 - discount) / 100));
	//printf("%.2f\n",total*((100-discount)/100));
	memset(buffer, 0, sizeof(buffer));
	printf("Total Price: %.2f NIS (Confirm to approve/else cancel)\n", name2);

	if ((rbytes = read(0, &buffer, BUF)) == -1) { perror("read"); exit(1); }
	if (strcmp(buffer, "Confirm\n") == 0) {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		write(to, "Total Price: ", strlen("Total Price: "));
		//sprintf(temp,"%fcheck",total);
		//write(to,temp,strlen(temp));
		write(to, name2, strlen(name2));
		//sprintf(temp, "%.2f", totalPrice);
		//write (to, temp, strlen(temp));
		write(to, " NIS\n", 4);
		sprintf(temp, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		write(to, temp, strlen(temp));
		write(to, "\n", 1);
		printf("Order created!\n");
	}
	else if (strcmp(buffer, "Cancel\n") == 0) {
		close(to);
		if ((pid = fork()) == 0) {
			execl("/bin/rm", "rm", dirname, NULL);
			if (errno) {
				printf("Can't cancel\n");
				exit(1);
			}
		}
		waitpid(pid);
		exit(0);
	}

	close(to);
	exit(0);

}














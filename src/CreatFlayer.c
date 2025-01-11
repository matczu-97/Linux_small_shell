
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>


#define BUF 200
#define O1 "Enjoyed"
#define O2 "shop Now and have fun"
#define O3 "have fun"
#define O4 "other"

//allocating new memory
void updating(char*** arr, char* token, int* i) {
	(*arr) = (char**)realloc(*arr, ((*i) + 1) * sizeof(char*));
	(*arr)[*i] = (char*)malloc(30 * sizeof(char));
	strcpy((*arr)[*i], token);
	(*i)++;

}






int main(int argc, char* argv[])
{
	if (argc != 3) {
		printf("ERROR");
		exit(1);
	}
	int k;
	int rbytes, i = 1, j;//flag check if company in file
	char buffer[BUF] = { "" };
	char* token;//to go over lines
	char** arr;//to save the input
	int to;
	int n;//check option
	char dirname[BUF] = { "" };
	char* p, temp[40] = { "" };
	int count = 0;//check number of spaces
	char only_name[40] = { "" };//spread rhe string to name and price
	char to_write[BUF] = { "" };
	strcat(dirname, argv[1]);
	strcat(dirname, "_Order");
	mkdir(dirname, 0777);
	to = open("Black_Friday/camp_partic.txt", O_RDWR | O_APPEND);
	if (to == -1) { perror("open"); exit(1); }
	write(to, argv[1], strlen(argv[1]));
	write(to, "\n", 1);
	close(to);
	sprintf(to_write, "%s.txt", argv[1]);//writing to create file .txt
	to = open(to_write, O_WRONLY | O_CREAT, 0644);
	memset(to_write, '\0', BUF);//refreshing to_write
	if (to == -1) { perror("open"); exit(1); }
	write(to, argv[1], strlen(argv[1]));
	write(to, " SALE\n", strlen(" SALE\n"));
	write(to, argv[2], strlen(argv[2]));
	write(to, "% off\n", strlen("% off\n"));
	printf("Insert item and item cost:\n");
	if ((rbytes = read(0, &buffer, BUF)) == -1) //read from stdin
	{
		perror("read"); exit(1);
	}
	token = strtok(buffer, "\n");
	arr = (char**)malloc(1 * sizeof(char*));//allocating
	arr[0] = (char*)malloc(30 * sizeof(char));
	strcpy(arr[0], token);//setting the first word
	while (strcmp(buffer, "Stop") != 0) {
		memset(buffer, '\0', BUF);
		if ((rbytes = read(0, &buffer, BUF)) == -1) //read from stdin
		{
			perror("read"); exit(1);
		}
		token = strtok(buffer, "\n");
		if (strcmp(buffer, "Stop") != 0) {
			updating(&arr, token, &i);//function allocating and setting words

		}
	}
	//creating promoting sentence
	memset(buffer, '\0', BUF);
	printf("What is your choice?\n1.%s\n2.%s\n3.%s\n4.%s\n", O1, O2, O3, O4);
	if ((rbytes = read(0, &buffer, 2)) == -1) //read from stdin
	{
		perror("read"); exit(1);
	}
	token = strtok(buffer, "\n");
	if (strcmp(buffer, "4") == 0) {
		printf("Insert your word:\n");
		memset(buffer, '\0', BUF);
		if ((rbytes = read(0, &buffer, 30)) == -1) //read from stdin

		{
			perror("read"); exit(1);
		}
		token = strtok(buffer, "\n");
		updating(&arr, token, &i);
	}
	else {//checking which sentence
		n = atoi(buffer);
		switch (n) {
		case 1:
		{
			updating(&arr, O1, &i);
			break;
		}
		case 2: {
			updating(&arr, O2, &i);
			break;
		}
		case 3:
		{
			updating(&arr, O3, &i);
			break;
		}
		default:
			break;
		}
	}

	//loop goes throw the list
	for (j = 0; j < i; j++) {
		count = 0;
		p = arr[j];
		p = p + strlen(arr[j]);//go to the end(to price)
		while (*p == '\0' || *p == ' ') { p--; }//go back
		if (*(p) < '0' || *(p) > '9')continue;//if there are no numbers this is the last sentence
		while (*p != ' ') {
			p--;
		}

		p++;//now p point to the number
		strcpy(temp, arr[j]);//create temp sstring
		token = strtok(temp, " ");//checking how many words until the last word(  the number number)
		while (token != NULL) {
			count++;
			token = strtok(NULL, " ");
		}


		strcpy(temp, arr[j]);//set temp again
		token = strtok(temp, " ");
		while (token != NULL) {
			if (count == 1)break;//if count=1 it is the end anf the number is infront
			strcat(only_name, token);
			strcat(only_name, " ");
			token = strtok(NULL, " ");
			count--;
		}

		strcat(to_write, only_name);//from here i am gussing not checked yet
		for (k = strlen(only_name); k < 30 - strlen(p); k++) {
			strcat(to_write, ".");
		}
		sprintf(to_write, "%s%sNIS\n", to_write, p);
		//printf("%s",to_write);
		write(to, to_write, strlen(to_write));
		memset(to_write, '\0', BUF);
		memset(only_name, '\0', BUF);
	}
	memset(to_write, '\0', BUF);
	sprintf(to_write, "%s\n", arr[i - 1]);
	write(to, to_write, strlen(to_write));
	//printf("%15s",to_write);


	printf("Successfully created\n");
	close(to);
	exit(0);

}







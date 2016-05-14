///*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void Encrypt(FILE* stream, char name[], int month, int day);
void Decrypt(FILE* stream, char name[], int month, int day);

int main(int argc, char* argv[])
{
	struct tm *t;
	time_t timer = time(NULL);
	t = localtime(&timer);
	//t->tm_year + 1900
	//t->tm_mon + 1 : use1
	//t->tm_mday : use2
	//t->tm_hour
	//t->tm_min
	//t->tm_sec
	//mday*mday+mon*mon

	FILE* fin;
	int i;
	int decryption = -1;

	puts("Released Date: 2015/08/29");
	puts("Recent Update: 2015/11/02");
	puts("Copyright(c) 2015 rapsealk");
	puts("rscode v1.0 renikma");
	puts("※같은 경로에 파일이 저장됩니다.\n");

	if (argc == 1) {
		while (decryption != 0 && decryption != 1) {
			puts("0.encryption / 1.decryption");
			printf("Which one? ");
			scanf("%d", &decryption);
		}
		if (decryption) {
			Decrypt(stdin, "stdin.txt", t->tm_mon+1, t->tm_mday);
		}
		else {
			Encrypt(stdin, "stdin.txt", t->tm_mon+1, t->tm_mday);
		}
	}
	else if (argc >= 3) {
		if (!strcmp(argv[1], "decrypt")) {
			for (i = 2; i < argc; i++) {
				fin = fopen(argv[i], "r");
				Decrypt(fin, argv[i], t->tm_mon+1, t->tm_mday);
				fclose(fin);
			}
		}
		else if (!strcmp(argv[1], "encrypt")) {
			for (i = 2; i < argc; i++) {
				fin = fopen(argv[i], "r");
				Encrypt(fin, argv[i], t->tm_mon+1, t->tm_mday);
				fclose(fin);
			}
		}
	}
	else
		fprintf(stderr, "Invalid Input\n");

	return 0;
}
//*/

///*
void Encrypt(FILE* stream, char name[], int month, int day)
{
	FILE* save;
	char fname[30];
	char* point = NULL;
	int i, len;
	unsigned short std, term;
	char letter[2], result;
	
	strcpy(fname, name);
	len = strlen(fname);
	point = strchr(fname, '.');
	for (i = 4; i >= 0; i--)
		*(point + i + 4) = *(point + i);
	*(point) = '_';
	*(point+1) = 'e';
	*(point+2) = 'n';
	*(point+3) = 'c';

	save = fopen(fname, "w");

	i = 0;
	while (fgets(letter, 2, stream) != NULL) {
		if ('a' <= letter[0] && letter[0] <= 'z') {
			std = 'a';
			term = 26;
		}
		else if ('A' <= letter[0] && letter[0] <= 'Z') {
			std = 'A';
			term = 26;
		}
		else if ('0' <= letter[0] && letter[0] <= '9') {
			std = '0';
			term = 10;
		}
		else {
			fprintf(save, "%c", letter[0]);
			continue;
		}
		result = (letter[0] - std + (int)sqrt(pow(month, 3) + pow(day, 3) + pow(++i, 3)) + 1) % term + std;
		fprintf(save, "%c", result);
	}
	fclose(save);
}

void Decrypt(FILE* stream, char name[], int month, int day)
{
	FILE* save;
	char fname[30];
	char* point = NULL;
	int i, len;
	unsigned short std, term;
	char letter[2], result;

	strcpy(fname, name);
	len = strlen(fname);
	point = strchr(fname, '.');
	for (i = 4; i >= 0; i--)
		*(point + i + 4) = *(point + i);
	*(point) = '_';
	*(point + 1) = 'd';
	*(point + 2) = 'e';
	*(point + 3) = 'c';

	save = fopen(fname, "w");

	i = 0;
	while (fgets(letter, 2, stream) != NULL) {
		if ('a' <= letter[0] && letter[0] <= 'z') {
			std = 'a';
			term = 26;
		}
		else if ('A' <= letter[0] && letter[0] <= 'Z') {
			std = 'A';
			term = 26;
		}
		else if ('0' <= letter[0] && letter[0] <= '9') {
			std = '0';
			term = 10;
		}
		else {
			fprintf(save, "%c", letter[0]);
			continue;
		}
		result = std + (term * 20 + (letter[0] - std) - ((int)sqrt(pow(month, 3) + pow(day, 3) + pow(++i, 3)) + 1)) % term;
		//result = (letter - std + (int)sqrt(pow(month, 3) + pow(day, 3)) + 1) % term + std;
		fprintf(save, "%c", result);
	}
	fclose(save);
	//outmsg[idx] = std + (term * 10 + (inmsg[idx] - std) - (idx + 1)) % term;
}
//*/

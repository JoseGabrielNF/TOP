#include <stdio.h>
#include <time.h>
#include <ncurses.h> 
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#define processoexibido 17
char word[100];
int compara_func;
typedef struct mytop
{
	char USER[100];
	long long int PR;
	char S[10];
	double CPU;
	double TIME;
	char COMMAND[100];
	char pid[1000];
} estrutura;
void getuserid();
void getusername();
void getstat();
void getprocpid();
int  compara(); 
void printupside();
void imprime();
void apaga();
void ler();


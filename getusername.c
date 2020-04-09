#include <stdio.h>
#include <string.h>
#include <ncurses.h>

void getusername(char usr[100][100], char id[100][100] , char USER[100], char *pid)
{
	FILE *arq;
	char mystring[100];
	char folder[100];
	char userid1[100];


    //Concatena o pid com o caminho do arquivo /proc/pid/status
	strcpy(folder, "/proc/");
	strcat(folder, pid);
	strcat(folder, "/status");

     //Abre o arquivo
	arq = fopen(folder, "r");

	if (arq == NULL){
		//arquivo não encontrado
		endwin();
		return ;
	
	}
	else
	{
		while (1)
		{
			//Procura palavra por palavra até achar a palavra "Uid:" 
			fscanf(arq, "%s", mystring);
			if (strcmp(mystring, "Uid:") == 0)
			{
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				break;
			}
			
		}
	}

	//Faz uma busca nos vetores userid e userid2 procurando pelo usuário daquele id
	//strcmp = comparar dois valores e retorna 0 se forem iguais
	//strcat = (string=string) atribui uma string na outra
	for (int i = 0; strcmp(usr[i], "7"); i++)
	{
		if (strcmp(userid1, id[i]) == 0 )
		{
			
			//Copia o usuário encontrado e formata no tamanho 7 pra caber no terminal
			int j;
			for(j=0;usr[i][j]!='\0'&&j<=7;j++)
			{
				USER[j]=usr[i][j];
			}
			if(j==8){
			USER[j-1]='+';
			}
			USER[j]='\0';
			
			fclose(arq);
			return;
		}
	}
	strcpy(USER, "error");
	fclose(arq);
}

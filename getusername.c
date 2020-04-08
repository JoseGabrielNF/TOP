#include <stdio.h>
#include <string.h>

void getusername(char usr[100][100], char id[100][100], char id2[100][100], char USER[100], char *pid)
{
	FILE *arq;
	char mystring[100];
	char folder[100];
	char userid1[100];
	char userid2[100];

    //Concatena o pid com o caminho do arquivo /proc/pid/status
	strcpy(folder, "/proc/");
	strcat(folder, pid);
	strcat(folder, "/status");

     //Abre o arquivo
	arq = fopen(folder, "r");

	if (arq == NULL)
		perror("Error opening file");
	else
	{
		while (1)
		{
			//Procura palavra por palavra até achar a palavra "Uid:" depois continua lendo pra pegar os 2 identificadores de usuário
			fscanf(arq, "%s", mystring);
			if (strcmp(mystring, "Uid:") == 0)
			{
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", userid1);
				fscanf(arq, "%s", mystring);
				fscanf(arq, "%s", userid2);
				break;
			}
			fflush(stdin);
		}
	}

	//Faz uma busca nos vetores userid e userid2 procurando pelo usuário daquele id
	//strcmp = comparar dois valores e retorna 0 se forem iguais
	//strcat = (string=string) atribui uma string na outra
	for (int i = 0; strcmp(usr[i], "7"); i++)
	{
		if (strcmp(userid1, id[i]) == 0 && strcmp(userid2, id2[i]) == 0)
		{
			strcpy(USER, usr[i]);
			fclose(arq);
			return;
		}
	}
	strcpy(USER, "errorname");
	fclose(arq);
}

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void getstat(long int *PR, char S[10], double *CPU, double *TIME, char COMMAND[100], char *pid)
{
  FILE *arq;
  char folder[100];
  char aux[100];
  long unsigned int utime, stime;
  long int cutime, cstime;
  long long unsigned int starttime;
  long unsigned int tempo;
  int uptime;
  int clock = sysconf(_SC_CLK_TCK);

  char AUXCOMMAND[100];
  //Concatena o pid com o caminho do arquivo /proc/pid/stat
  strcpy(folder, "/proc/");
  strcat(folder, pid);
  strcat(folder, "/stat");

  //Abre o arquivo
  arq = fopen(folder, "r");

  if (arq == NULL)
    perror("Error opening file");
  else
  {
    //Escaneia o arquivo usando um vetor auxiliar nas informações que não são necessárias

    fscanf(arq, "%s", aux);          //pid %d 1
    fscanf(arq, "%s", AUXCOMMAND);   //comm %s 2
    fscanf(arq, "%s", S);            // state %c 3
    fscanf(arq, "%s", aux);          //ppid %d 4
    fscanf(arq, "%s", aux);          //pgrp %d 5
    fscanf(arq, "%s", aux);          //session %d 6
    fscanf(arq, "%s", aux);          //tty_nr %d 7
    fscanf(arq, "%s", aux);          //tpgid %d 8
    fscanf(arq, "%s", aux);          //flags %u 9
    fscanf(arq, "%s", aux);          //minflt %lu 10
    fscanf(arq, "%s", aux);          //cminflt %lu 11
    fscanf(arq, "%s", aux);          //majflt %lu 12
    fscanf(arq, "%s", aux);          //cmajflt %lu 13
    fscanf(arq, "%lu", &utime);      //utime %lu 14
    fscanf(arq, "%lu", &stime);      //stime %lu 15
    fscanf(arq, "%ld", &cutime);     //cutime %ld 16
    fscanf(arq, "%ld", &cstime);     //cstime %ld 17
    fscanf(arq, "%ld", PR);          //priority %ld 18
    fscanf(arq, "%s", aux);          //nice %ld 19
    fscanf(arq, "%s", aux);          //num_threads %ld 20
    fscanf(arq, "%s", aux);          //itrealvalue  %ld 21
    fscanf(arq, "%llu", &starttime); //starttime  %llu 22
    fclose(arq);                     //fecha arquivo
  }

  //Cálculo do tempo de programa
  tempo = utime + stime;
  tempo = tempo + cutime + cstime;
  //Abre o arquivo uptime contendo as informações sobre o inicio do sistema
  FILE *up;
  up = fopen("/proc/uptime", "r");
  if (up == NULL)
    perror("Error opening file");
  else
  {
    fscanf(up, "%d", &uptime);
    
    fclose(up);
  }
  //Cálculo do tempo de programa com horário do sistema
  (*TIME) = uptime - (starttime / clock);
  //Cálculo do uso da cpu
  (*CPU) = 100 * ((tempo / clock) / (*TIME));


   if((*PR)<-20)
   {
     (*PR)=0;
   }
  //For pra retirar os parênteses () do arquivo command
  int i;
  int j = 0;
  for (i = 1; AUXCOMMAND[i] != '\0'; i++)
  {

    COMMAND[j] = AUXCOMMAND[i];
    j++;
  }
  COMMAND[i - 2] = '\0';

  return;
}
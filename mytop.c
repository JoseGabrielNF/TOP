#include <stdio.h>
#include <stdlib.h>
#include <mytop.h>
#include <time.h>
#include <ncurses.h> //biblioteca ncurses
#include<unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>



typedef struct mytop {
	char USER [100];	 
	long long int PR;
	char S[10];
	double CPU;
	double TIME;
	char COMMAND[100];  
	char pid [1000];
}a;



void imprime(int in, struct mytop dados[1000]);
void ler(struct mytop * Dados,int QTDPIDS,int PIDS[5000]);
int comparacpu(const void *p1, const void *p2);
int comparanome(const void *p1, const void *p2);
int comparapid(const void *p1, const void *p2);
int comparatempo(const void *p1, const void *p2);


int main(void) {
	int PIDS[5000];
	int QTDPIDS;
	int i=0;
    
    //Inicializa o ncurses
     initscr();
	 
	//Esconde o cursor
	curs_set(0);
	//Esta função torna possível o uso das cores
     start_color();	
	//Texto branco, fundo preto e depois inicializa com a função attron()
	
	init_pair(1,COLOR_BLACK,COLOR_WHITE);
	attron(COLOR_PAIR(1));
	
	//Laço para pintar a linha do cabeçalho
	for(i=0; i<100; i++)
		printw(" ");
	
	//Cabeçalho da interface
	
	move(0,0);
	printw("PID");
	move(0,10);
	printw("USER");
	move(0,20);
	printw("PR");
	move(0,30);
	printw("S");
	move(0,40);
	printw("%%CPU");
	move(0,50);
	printw("TEMPO");
	move(0,60);
	printw("COMMAND");
	
	//Desabilitando o par de cores anterior para o padrão
	attroff(COLOR_PAIR(1)); 		

	while(1) {
		
		struct mytop Dados[1000];
		//Ler 
		getprocpid(&PIDS,&QTDPIDS);
        ler(Dados,QTDPIDS,PIDS); 
		qsort (Dados, QTDPIDS, sizeof(a), comparacpu); 
		//Lista os processos na interface
		for(i=0; (i<15&&i<QTDPIDS); i++){
			
			imprime(i, Dados);
            refresh();  	
		}
		sleep(1);
	}
	endwin();  
	return (0);  
}

void ler(struct mytop Dados[1000],int QTDPIDS,int PIDS[5000])
{

    char usr[100][100];
	char id[100][100];
	char id2[100][100];	
	int i;
	for(i=0;i<QTDPIDS;i++){
    
	sprintf(Dados[i].pid, "%d", PIDS[i]); 
		  
	//Duas Funções ultilizadas para retornar o nome do usuário dono do processo

	getuserid(usr,id,id2);
	getusername(usr,id, id2, &Dados[i].USER, Dados[i].pid);  
	
	//Função para extrair os dados do arquivo stat
	getstat(&Dados[i].PR, &Dados[i].S, &Dados[i].CPU, &Dados[i].TIME, &Dados[i].COMMAND, &Dados[i].pid); 
	  
	}
	return;
};

void imprime(int i, struct mytop Dados[1000]){
	  
	move(i+1,0);
	printw("%s",Dados[i].pid);
	move(i+1,10);
	printw("%s",Dados[i].USER);
	move(i+1,20);
	printw("%lld",Dados[i].PR);
	move(i+1,30);
	printw("%s",Dados[i].S);
	move(i+1,40);
	printw("%.2f%%",Dados[i].CPU);
	move(i+1,50);
	printw("%d:", (int)(Dados[i].TIME) / 60 % 60 / 24);
	printw("%d.", (int)(Dados[i].TIME) / 60 % 60);
	printw("%d", (int)(Dados[i].TIME) % 60);
	move(i+1,60);
	printw("./%s",Dados[i].COMMAND);
   
}




int comparacpu(const void *p1, const void *p2)
{
    const struct mytop *elem1 = p1;    
    const struct mytop *elem2 = p2;

   if (elem1->CPU > elem2->CPU)
      return -1;
   else if (elem1->CPU < elem2->CPU)
      return 1;
   else
      return 0;
}
int comparapid(const void *p1, const void *p2)
{
    const struct mytop *elem1 = p1;    
    const struct mytop *elem2 = p2;

   if (atoi(elem1->pid) < atoi(elem2->pid))
      return -1;
   else if (atoi(elem1->pid) > atoi(elem2->pid))
      return 1;
   else
      return 0;
}
int comparanome(const void *p1, const void *p2)
{
    const struct mytop *elem1 = p1;    
    const struct mytop *elem2 = p2;

   return strcmp(elem1->USER,elem2->USER); 
}
int comparatempo(const void *p1, const void *p2)
{
    const struct mytop *elem1 = p1;    
    const struct mytop *elem2 = p2;

   if (elem1->TIME > elem2->TIME)
      return -1;
   else if (elem1->TIME < elem2->TIME)
      return 1;
   else
      return 0;
}
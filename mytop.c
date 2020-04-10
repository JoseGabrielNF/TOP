#include <mytop.h>


int main(void)
{
	int PIDS[5000];
	int QTDPIDS,QTDPIDSatual;
	int i = 0;
	
	//Inicializa o ncurses
	initscr();
	//Esconde o cursor
	curs_set(0);
	//Inicializa cores
	start_color();	
	//Carrega cor do arquivo config
    abrearquivodecor();
	
	//ativa cor
	bkgd(COLOR_PAIR(1));    
	attron(COLOR_PAIR(1));	
	attron(COLOR_PAIR(2));

    //pinta o cabeçalho da interface
	pintaInterface();
	
	struct mytop Dados[1000];
	int linha_inicial = 0;
	
	while (1)
	{
		
		//Le diretorio proc
		getprocpid(&PIDS, &QTDPIDS);
	
        //Le arquivos proc
		ler(Dados, QTDPIDS, PIDS);
	   
        //Ordena quando necessário
		qsort(Dados, QTDPIDS, sizeof(estrutura), compara);
		//Printa
		for (i=0; (i < processoexibido && i < QTDPIDS); i++)
		{
			imprime(i, Dados, linha_inicial + i, QTDPIDS);
			refresh();
		}
		//atualiza o proceso quantidade de processosa ativos e processo selecionado
	    attron(COLOR_PAIR(2));
        mvprintw(0, 70, "P:(%d)  ", QTDPIDS);
		attroff(COLOR_PAIR(2));
		refresh();
        
		//Pausa por 0.3 segundos para diminuir o uso de cpu
		timeout(300);
		noecho();
		char c = getch();	
	
        //Condições de cada tecla pressionada
		lertecla(c,&linha_inicial,QTDPIDS,Dados);
	}
	endwin();
	return (0);
}

void ler(struct mytop * Dados, int QTDPIDS, int PIDS[5000])
{
	//vetores com a lista de usuários da maquina
	char usr[100][100];
	char id[100][100];
	//preenche vetor
	getuserid(usr, id);

	int i;
	for (i = 0; i < QTDPIDS; i++)
	{
		sprintf(Dados[i].pid, "%d", PIDS[i]);
		//retornar o nome do usuário dono do processo com base no id obtido na função anterior
		getusername(usr, id, &Dados[i].USER, Dados[i].pid);

		//função para extrair os dados do arquivo stat
		getstat(&Dados[i].PR, &Dados[i].S, &Dados[i].CPU, &Dados[i].TIME, &Dados[i].COMMAND, &Dados[i].pid);
	}
	return;
};

void imprime(int i, struct mytop *Dados, int linha, int QTDPIDS)
{	
	if(i==0){
		//printa selecionado
		attron(COLOR_PAIR(3));
	    int linha, coluna,j;
	    getmaxyx(stdscr,linha,coluna);
		for(j=0;j<coluna;j++)
		{
			mvprintw(1,j," ");
		}	
			
	}
	//apagar a linha caso atinja o limite
	if (linha >= QTDPIDS)
	{
		int k;
		for(k=i+1;k<=processoexibido;k++){
		move(k, 0);
		clrtoeol();
		}
	}
	else
	{
		mvprintw(i + 1, 0, "%s                  ", Dados[linha].pid);
		mvprintw(i + 1, 10, "%s                 ", Dados[linha].USER);
		mvprintw(i + 1, 20, "%lld               ", Dados[linha].PR);
		mvprintw(i + 1, 30, "%s                 ", Dados[linha].S);
		mvprintw(i + 1, 40, "%.2f%%             ", Dados[linha].CPU);
		mvprintw(i + 1, 50, "%d:", (int)(Dados[linha].TIME) / 60 % 60 / 24);
		printw("%d.", (int)(Dados[linha].TIME) / 60 % 60);
		printw("%d             ", (int)(Dados[linha].TIME) % 60);
		mvprintw(i + 1, 60, "./%s", Dados[linha].COMMAND);	
	   attroff(COLOR_PAIR(3));
	}
}


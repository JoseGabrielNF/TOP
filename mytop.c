#include <mytop.h>

void lertecla();

int main(void)
{
	int PIDS[5000];
	int QTDPIDS;
	int i = 0;

	//Inicializa o ncurses
	initscr();

	//Esconde o cursor
	curs_set(0);
	//Esta função torna possível o uso das cores
	start_color();

    //inicia cores
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
    
	//ativa cor
	attron(COLOR_PAIR(1));

	//Laço para pintar a linha do cabeçalho
	int j;
	for (j = 0; j < 80; j++)
		printw(" ");

	//Cabeçalho da interface
	printupside();

	//Desliga cor
	attroff(COLOR_PAIR(1));

	//Textos fixos
	mvprintw(18, 0, "Selecionar \"setas\":");
	mvprintw(18, 20, "|");
	mvprintw(19, 20, "v");
	mvprintw(20, 0, "Ordernar: \"c\",\"p\",\"u\",\"t\" // cpu,pid,usuário,tempo");
	mvprintw(22, 0, "Matar processo \"k\" ");
	mvprintw(23, 0, "Sair \"q\" ");
	mvprintw(24, 0, "Localizar \"l\" :");
	mvprintw(0, 70, "P:%d", QTDPIDS);
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
		for (i = 0; (i < processoexibido && i < QTDPIDS); i++)
		{
			imprime(i, Dados, linha_inicial + i, QTDPIDS);
			refresh();
		}
		//atualiza o proceso quantidade de processosa ativos e processo selecionado
	    attron(COLOR_PAIR(1));
        mvprintw(0, 70, "P:(%d)  ", QTDPIDS);
		attroff(COLOR_PAIR(1));
		mvprintw(21, 0, "Matar Primeiro Processo:%s", Dados[linha_inicial].COMMAND);

		refresh();
        
		//Pausa por 0.1 segundos
		timeout(100);
		
		char c = getch();
	
        //Condições de cada tecla pressionada
		lertecla(c,&linha_inicial,QTDPIDS,Dados);
		//Apagar as linhas para evitar sobreescrita de palavras
		apaga();
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

	//apagar a linha caso atinja o limite
	if (linha >= QTDPIDS)
	{
		move(i + 1, 0);
		clrtoeol();
	}
	else
	{
		mvprintw(i + 1, 0, "%s", Dados[linha].pid);
		mvprintw(i + 1, 10, "%s", Dados[linha].USER);
		mvprintw(i + 1, 20, "%lld", Dados[linha].PR);
		mvprintw(i + 1, 30, "%s", Dados[linha].S);
		mvprintw(i + 1, 40, "%.2f%%", Dados[linha].CPU);
		mvprintw(i + 1, 50, "%d:", (int)(Dados[linha].TIME) / 60 % 60 / 24);
		printw("%d.", (int)(Dados[linha].TIME) / 60 % 60);
		printw("%d", (int)(Dados[linha].TIME) % 60);
		mvprintw(i + 1, 60, "./%s", Dados[linha].COMMAND);
	}
}
void apaga()
{
	//Apaga todas as linhas ,pra não ter palavras por cima das outras
	int i = processoexibido;
	for (i = 1; i <= processoexibido; i++)
	{
		move(i, 0);
		clrtoeol();
	}
	move(21, 0);
	clrtoeol();
}
void printupside()
{
	//printa a parte de cima da tela
	mvprintw(0, 0, "PID");
	mvprintw(0, 10, "USER");
	mvprintw(0, 20, "PR");
	mvprintw(0, 30, "S");
	mvprintw(0, 40, "%%CPU");
	mvprintw(0, 50, "TEMPO");
	mvprintw(0, 60, "COMMAND");
}

#include <mytop.h>

//Códigos da interface com as funções de pintarcabeçalho,abrir,salvar,abrir interface de pintar,abrir interface do manual 

void pintaInterface()
{
	move(0,0);
	int linha, coluna;;
	getmaxyx(stdscr,linha,coluna);
	//Laço para pintar a linha do cabeçalho
	attron(COLOR_PAIR(2));
	for(int i=0; i<coluna; i++){
		mvprintw(0,i," ");
	}	
	//Cabeçalho da interface
	printupside();
	attroff(COLOR_PAIR(2));
	refresh();
}
void printupside()
{
	//printa a parte de cima da tela
	mvprintw(0,0, "PID");
	mvprintw(0,10, "USER");
	mvprintw(0,20, "PR");
	mvprintw(0,30, "S");
	mvprintw(0,40, "%%CPU");
	mvprintw(0,50, "TIME");
	mvprintw(0,60, "COMMAND");
}

void abrearquivodecor()
{

	FILE *arq;
	arq = fopen("config","r");
	//arquivo não encontrado
	if (arq == NULL){
		perror("Error config not found");	
	}
	else
	{
		//inicia cores salvas
		int linha,opcao,cor1,cor2,aux;
		for(int i=0; i<3; i++){
			fscanf(arq,"%d", &linha);
			opcao = linha/100;
			aux = linha/10;
			cor1 = aux%10;
			aux = linha%100;
			cor2 = aux%10;
			if(opcao == 1)
				init_pair(1, cor1, cor2);
			if(opcao == 2)
				init_pair(2, cor1, cor2);
			if(opcao == 3)
				init_pair(3, cor1, cor2);
		}
		fclose(arq);
	}

}
void salvarcor(char opcao, char cor1, char cor2)
{

    FILE *arq;
    arq = fopen("config", "r");
    int background, cabecalho, selecao;
    //Faz a leitura do arquivo config
    fscanf(arq, "%d %d %d", &background, &cabecalho, &selecao);
    fclose(arq);
    arq = fopen("config", "w");
    //arquivo não encontrado
    if (arq == NULL)
    {
        perror("Error opening file config");
    }
    else
    {
        //Salva as novas configurações de cores
        if ((opcao - '0') == 1)
        {
            fprintf(arq, "%d%d%d\n", 1, (cor1 - '0'), (cor2 - '0'));
            fprintf(arq, "%d\n", cabecalho);
            fprintf(arq, "%d", selecao);
        }
        if ((opcao - '0') == 2)
        {
            fprintf(arq, "%d\n", background);
            fprintf(arq, "%d%d%d\n", 2, (cor1 - '0'), (cor2 - '0'));
            fprintf(arq, "%d", selecao);
        }
        if ((opcao - '0') == 3)
        {
            fprintf(arq, "%d\n", background);
            fprintf(arq, "%d\n", cabecalho);
            fprintf(arq, "%d%d%d", 3, (cor1 - '0'), (cor2 - '0'));
        }
        fclose(arq);
    }
}

void selecaodecores(char *opcao, char *cor1, char *cor2)
{
    int x, y;
    move(0, 0);
    clrtobot();
    getmaxyx(stdscr, x, y);
    mvprintw(0, 0, "MYTOP(1)");
    char titulo[] = "PERSONALIZACAO DE CORES";
    mvprintw(0, (y - strlen(titulo)) / 2, "%s", titulo);
    mvprintw(3, 0,
             "	As cores para a personalização da interface estão disponíveis "
             "conforme a tabela abaixo:\n\n");

    mvprintw(6, 0, "	Passo 1 - Alterar esquema de cores			0 - PRETO	");
    init_pair(4, 0, 0);
    attron(COLOR_PAIR(4));
    printw("	");
    attroff(COLOR_PAIR(4));

    mvprintw(7, 0, "	   1) Background					1 - VERMELHO	");
    init_pair(5, 1, 1);
    attron(COLOR_PAIR(5));
    printw("	");
    attroff(COLOR_PAIR(5));

    mvprintw(8, 0, "	   2) Cabeçalho					2 - VERDE	");
    init_pair(6, 2, 2);
    attron(COLOR_PAIR(6));
    printw("	");
    attroff(COLOR_PAIR(6));

    mvprintw(9, 0, "	   3) Seleção						3 - AMARELO	");
    init_pair(7, 3, 3);
    attron(COLOR_PAIR(7));
    printw("	");
    attroff(COLOR_PAIR(7));

	mvprintw(10,0,"								4 - AZUL	");	
    init_pair(8,4,4);
	attron(COLOR_PAIR(8));
	printw("	");
	attroff(COLOR_PAIR(8));
		
	mvprintw(11,0,"	Passo 2 - Informar o número da cor da LETRA		5 - MAGENTA	");
	init_pair(9,5,5);
	attron(COLOR_PAIR(9));
	printw("	");
	attroff(COLOR_PAIR(9));

    mvprintw(12, 0, "								6 - CIANO	");
    init_pair(10, 6, 6);
    attron(COLOR_PAIR(10));
    printw("	");
    attroff(COLOR_PAIR(10));

    mvprintw(13, 0, "	Passo 3 - Informar o número da cor de FUNDO		7 - BRANCO	");
    init_pair(11, 7, 7);
    attron(COLOR_PAIR(11));
    printw("	");
    attroff(COLOR_PAIR(11));

    curs_set(1);
    echo();

    while (1)
    {
        mvprintw(18, 0, "	Informe qual esquema de cores deseja alterar: ");
        (*opcao) = getch();
        if ((*opcao) >= '1' && (*opcao) <= '3')
        {
            break;
        }
    }

    while (1)
    {
        mvprintw(19, 0, "	Informe o numero da cor da LETRA: ");
        (*cor1) = getch();
        if ((*cor1) >= '0' && (*cor1) <= '7')
        {
            break;
        }
    }

    while (1)
    {
        mvprintw(20, 0, "	Informe o número da cor de FUNDO: ");
        (*cor2) = getch();
        if ((*cor2) >= '0' && (*cor2) <= '7')
        {
            move(0, 0);
            clrtobot();
            refresh();

            break;
        }
    }

    if ((*opcao) == '1') //background
        init_pair(1, ((*cor1) - '0'), ((*cor2) - '0'));
    if ((*opcao) == '2') //cabeçalho
        init_pair(2, ((*cor1) - '0'), ((*cor2) - '0'));
    if ((*opcao) == '3') //seleção
        init_pair(3, ((*cor1) - '0'), ((*cor2) - '0'));

    move(0, 0);
    clrtobot();
    pintaInterface();
    noecho();
    curs_set(0);
}



void manual(int c)
{
    int x, y;
    move(0, 0);
    clrtobot();
    getmaxyx(stdscr, x, y);
    mvprintw(0, 0, "MYTOP(1)");
    char titulo[] = "Comandos de Usuário";
    mvprintw(0, (y - strlen(titulo)) / 2, "%s", titulo);
    mvprintw(3, 0,
             "NOME\n"
             "     MyTop - exibe os processos do sistema operacional Linux\n\n"
             "DESCRICAO\n"
             "     O programa MyTop lista em tempo real os processos que são "
             "gerenciados pelo kernel do Linux. O usuário pode alterar "
             "a forma de vizualizar os dados, podendo ser pelo número do ID "
             "do processo, pelo nome de usuário, pela porcentagem do uso "
             "de CPU ou pelo tempo de execução, além de poder alterar as "
             "opções de cores da interface. Oferece a opção de localizar "
             "um determinado processo fornecendo o seu nome e a opção de "
             "finalizá-lo.\n\n"
             "OPERACAO\n"
             "     [TECLA]		[OBJETIVO]\n"
             "     Seta baixo		Desce uma linha\n"
             "     Seta cima		Sobe uma linha\n"
             "     c			Ordena visualização baseado no CPU\n"
             "     p			Ordena visualização baseado no PID\n"
             "     u			Ordena visualização baseado no USER\n"
             "     t			Ordena visualização baseado no TIME\n"
             "     l			Localiza um determinado processo\n"
             "     k			Finaliza o processo selecionado\n"
             "     m			Altera as cores da interface\n"
             "     h/?		Abre a ajuda do aplicativo\n"
             "     q			Fecha o aplicativo\n\n"
             "Pressione qualquer tecla para voltar...");
    refresh();
    while ((c = getchar()) == '\n')
        ;

    move(0, 0);
    clrtobot();
    pintaInterface();
}
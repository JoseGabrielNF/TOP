#include <mytop.h>
#include <stdio.h>
#include <stdlib.h>

void lertecla(char c, int * linha_inicial, int QTDPIDS,struct mytop *Dados)
{
	int x, y, opcao;
    if (c=='q')//fechar janela
    {
        endwin();
        exit(0);
    }
    if (c=='m')//altera a cor da interface
    {
		move(0,0);
		clrtobot();
		getmaxyx(stdscr,x,y);
		mvprintw(0,0, "MYTOP(1)");
		char titulo[]= "PERSONALIZACAO DE CORES";
		mvprintw(0,(y-strlen(titulo))/2,"%s", titulo);
		mvprintw(3,0,
		"	As cores para a personalização da interface estão disponíveis "
		"conforme a tabela abaixo:\n\n");
		
		mvprintw(6,0,"	Passo 1 - Alterar esquema de cores			0 - PRETO	"); 		
		init_pair(4,0,0);
		attron(COLOR_PAIR(4));
		printw("	");		
		attroff(COLOR_PAIR(4));
		
		mvprintw(7,0,"	   1) Background					1 - VERMELHO	");
		init_pair(5,1,1);
		attron(COLOR_PAIR(5));
		printw("	");
		attroff(COLOR_PAIR(5));
		
		mvprintw(8,0,"	   2) Cabeçalho					2 - VERDE	");
		init_pair(6,2,2);
		attron(COLOR_PAIR(6));
		printw("	");
		attroff(COLOR_PAIR(6));
		
		mvprintw(9,0,"	   3) Seleção						3 - AMARELO	");		
		init_pair(7,3,3);
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
		
		mvprintw(12,0,"								6 - CIANO	");
		init_pair(10,6,6);
		attron(COLOR_PAIR(10));
		printw("	");
		attroff(COLOR_PAIR(10));
		
		mvprintw(13,0,"	Passo 3 - Informar o número da cor de FUNDO		7 - BRANCO	");
		init_pair(11,7,7);
		attron(COLOR_PAIR(11));
		printw("	");
		attroff(COLOR_PAIR(11));

        int i=0;
        mvprintw(18,0,"	Informe qual esquema de cores deseja alterar: ");
        curs_set(1);
		
		char opcao;
		for (i = 0;;)
		{
			opcao = getch();
			if(opcao=='1' || opcao=='2' || opcao=='3')
				break;
		}
		char cor1;
		mvprintw(19,0,"	Informe o numero da cor da LETRA: ");
		for (i = 0;;)
		{
			cor1 = getch();
			if(cor1=='0' || cor1=='1' || cor1=='2' || cor1=='3' || cor1=='4' || cor1=='5' || cor1=='6' || cor1=='7')
				break;
		}
		char cor2;
		mvprintw(20,0,"	Informe o número da cor de FUNDO: ");
		for (i = 0;;)
		{
			cor2 = getch();
			if(cor2=='0' || cor2=='1' || cor2=='2' || cor2=='3' || cor2=='4' || cor2=='5' || cor2=='6' || cor2=='7')
				break;
		}		

		if (opcao == '1')//background
			init_pair(1,(cor1-'0'),(cor2-'0'));
		if (opcao == '2')//cabeçalho
			init_pair(2,(cor1-'0'),(cor2-'0'));
		if (opcao == '3')//seleção
			init_pair(3,(cor1-'0'),(cor2-'0'));
		
		//Carrega o caminho do diretório atual
		char cwd[PATH_MAX];
		getcwd(cwd, sizeof(cwd));
		//Concatena com o arquivo de configuração
		strcat(cwd, "/config");
		
		FILE *arq;
		arq = fopen(cwd,"r");
		int background,cabecalho,selecao;
		//Faz a leitura do arquivo config
		fscanf(arq,"%d %d %d", &background, &cabecalho, &selecao);
		fclose(arq);	
		arq = fopen(cwd,"w");		
		//arquivo não encontrado
		if (arq == NULL){
			perror("Error opening file config" );
		}
		else			
		{	
			//Salva as novas configurações de cores
			if((opcao-'0') == 1) {
				fprintf(arq,"%d%d%d\n",1,(cor1-'0'),(cor2-'0'));
				fprintf(arq,"%d\n",cabecalho);
				fprintf(arq,"%d",selecao);
			}
			if((opcao-'0') == 2) {
				fprintf(arq,"%d\n",background);
				fprintf(arq,"%d%d%d\n",2,(cor1-'0'),(cor2-'0'));
				fprintf(arq,"%d",selecao);
			}
			if((opcao-'0') == 3) {
				fprintf(arq,"%d\n",background);
				fprintf(arq,"%d\n",cabecalho);
				fprintf(arq,"%d%d%d",3,(cor1-'0'),(cor2-'0'));
			}
			fclose(arq);		
		}		
		curs_set(0);
    }
	if (c=='h' || c=='?')//abre a ajuda
    {
		move(0,0);
		clrtobot();
		getmaxyx(stdscr,x,y);
		mvprintw(0,0, "MYTOP(1)");
		char titulo[]= "Comandos de Usuário";
		mvprintw(0,(y-strlen(titulo))/2,"%s", titulo);		
		mvprintw(3,0,
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
		"     p			Ordena visualização baseado no PID\n"
		"     u			Ordena visualização baseado no USER\n"
		"     c			Ordena visualização baseado no CPU\n"
		"     t			Ordena visualização baseado no TIME\n"
		"     l			Localiza um determinado processo\n"
		"     k			Finaliza o processo selecionado\n"
		"     m			Altera as cores da interface\n"
		"     h/?		Abre a ajuda do aplicativo\n"
		"     q			Fecha o aplicativo\n\n"
		"Pressione qualquer tecla para voltar...");
        refresh();
		while ((c = getchar())=='\n');
    }
    if (c=='B')//seta bra baixo;
    {
        if ((*linha_inicial) < QTDPIDS)
        {
            (*linha_inicial)++;
        }
    }
    if (c=='A')//seta pra cima
    {        
        if ((*linha_inicial) >= 1)
        {
            (*linha_inicial)--;
        }
    }
	
	//Altera a ordem de vizualização dos dados
    if (c=='c')//%CPU
    {
        compara_func = 0;
        (*linha_inicial) = 0;
    }
    if (c=='p')//PID
    {
        compara_func = 1;
        (*linha_inicial) = 0;
    }
    if (c=='u')//USER
    {
        compara_func = 2;
        (*linha_inicial) = 0;
    }
    if (c=='t')//TIME
    {
        compara_func = 3;
        (*linha_inicial) = 0;
    }
	
    if (c=='l')//Ler conteúdo digitado na tela
    {
        int i=0;
        mvprintw(18,0,"Informe o nome do processo: ");
        curs_set(1);
        for (i = 0;;)
        {
            char a = getch();
            if (a == '\n')//ler enter
            {
                curs_set(0);
                break;
            }
            if (a == 127)//ler backspace
            {
				getyx(stdscr,x,y);				
				if(y > 30) {
					mvprintw(x,y-3,"   ");
					move(x,y-3);
				}
                i = 0;
                continue;
            }
            if (a >= 'a' && a <= 'z'||a >= 'A' && a <= 'Z'||a >= '0' && a <= '9'||a=='/'||a=='-')
            {
                word[i] = a;//atualiza variavel global
                i++;
            }
        }
        word[i] = '\0';
        compara_func = 4;
        (*linha_inicial) = 0;
    }
    if (c=='k')//matar processo selecionado
	{
		attron(COLOR_PAIR(2));
		mvprintw(22, 30, "Matar(%s)? pressione k ou n", Dados[(*linha_inicial)].COMMAND);
		refresh();
		attroff(COLOR_PAIR(2));
		timeout(10000);//esperar por um resposta por 5 segundos
		int k = getch();
		if (k=='n'|| k==-1)//apagar aviso
		{				
			mvprintw(22, 30, "                                        ");
			refresh();
		}
		else if (k=='k')//matar processo
		{
			mvprintw(22, 30, "                                         ");
			char *args[100] = {"pkill"};
			char *args2[20];
			args2[0] = "pkill";
			args2[1] = Dados[(*linha_inicial)].COMMAND;
			args2[2] = NULL;

			pid_t pid = fork();//cria um fork pra printar fora da tela atual
			if (pid == 0)
			{
				endwin();
				execvp(*args, args2);
				clrtoeol();
				exit(0);
				return ;
			}
			else
			{
				clrtoeol();
			}
		}
	}
    return;
}
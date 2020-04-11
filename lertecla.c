#include <mytop.h>

void lertecla(char c, int *linha_inicial, int QTDPIDS, struct mytop *Dados)
{
	int x,y;
	if (c == 'q') //fechar janela
	{
		endwin();
		exit(0);
	}
	if (c == 'j')
	{
		clrtobot();
		refresh();
	}
	if (c == 'm') //altera a cor da interface
	{
		char opcao;
		char cor1;
		char cor2;
        selecaodecores(&opcao,&cor1,&cor2);
		salvarcor(opcao,cor1,cor2);
	}
	if (c == 'h' || c == '?') //abre a ajuda
	{
		manual(c);
		pintaInterface();
		
	}
	if (c == 'B') //seta bra baixo;
	{
		if ((*linha_inicial) < QTDPIDS-1)
		{
			(*linha_inicial)++;
		}
	}
	if (c == 'A') //seta pra cima
	{
		if ((*linha_inicial) >= 1)
		{
			(*linha_inicial)--;
		}
	}

	//Altera a ordem de vizualização dos dados
	if (c == 'c') //%CPU
	{   //printa a parte de cima da tela
		pintaInterface();
		attron(COLOR_PAIR(3));
		//tinge a seleção
	    mvprintw(0,40, "%%CPU");
		attroff(COLOR_PAIR(3));
		//altera a função compara global
		compara_func = 0;
		(*linha_inicial) = 0;
	}
	if (c == 'p') //PID
	{
		pintaInterface();
		attron(COLOR_PAIR(3));
	    mvprintw(0,0, "PID");
		attroff(COLOR_PAIR(3));
		
		compara_func = 1;
		(*linha_inicial) = 0;
	}
	if (c == 'u') //USER
	{
		pintaInterface();
		attron(COLOR_PAIR(3));
	    mvprintw(0,10, "USER");
		attron(COLOR_PAIR(3));
		compara_func = 2;
		(*linha_inicial) = 0;
	}
	if (c == 't') //TIME
	{
		pintaInterface();
		attron(COLOR_PAIR(3));
	    mvprintw(0,50, "TIME");
		attron(COLOR_PAIR(3));
		compara_func = 3;
		(*linha_inicial) = 0;
	}

	if (c == 'l') //Ler conteúdo digitado na tela
	{
		int i = 0;
		mvprintw(18, 0, "Informe o nome do commando:");
	    attron(COLOR_PAIR(3));
		mvprintw(19, 27, "press enter or backspace");
		attroff(COLOR_PAIR(3));
		move(18,27);

		echo();
		curs_set(1);
		for (i = 0;;)
		{
			char a = getch();
			if (a == '\n') //ler enter
			{
				curs_set(0);
				break;
			}
			if (a == 127) //ler backspace
			{
				move(18,27);
				clrtoeol();			
				i = 0;
				continue;
			}
			if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z' || a >= '0' && a <= '9' || a == '/' || a == '-')
			{
				word[i] = a; //atualiza variavel global
				i++;
			}
		}
		word[i] = '\0';
		move(18,0);
		clrtoeol();
		move(19,0);
		clrtoeol();
		compara_func = 4;
		(*linha_inicial) = 0;
	}
	if (c == 'k') //matar processo selecionado
	{
		attron(COLOR_PAIR(3));
		mvprintw(22, 30, "Matar(%s)? pressione k ou n", Dados[(*linha_inicial)].COMMAND);
		refresh();
		attroff(COLOR_PAIR(3));
		timeout(5000); //esperar por um resposta por 5 segundos
		int k = getch();
		if (k == 'n' || k == -1) //apagar aviso
		{
			mvprintw(22, 30, "                                          ");
			refresh();
		}
		else if (k == 'k') //matar processo
		{
			mvprintw(22, 30, "                                           ");
		    refresh();
			char *args[100] = {"pkill"};
			char *args2[20];
			args2[0] = "pkill";
			args2[1] = Dados[(*linha_inicial)].COMMAND;
			args2[2] = "-x";
			args2[3] = NULL;
            endwin();
			pid_t pid = fork(); //cria um fork pra printar fora da tela atual
			if (pid == 0)
			{
				execvp(*args, args2);
				exit(0);
			}
			else
			{
				clrtobot();
				wait(NULL);
				clrtobot();
			}
		}
	}
	return;
}
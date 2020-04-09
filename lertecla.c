#include <mytop.h>

void lertecla(char c, int * linha_inicial, int QTDPIDS,struct mytop *Dados)
{
    if (c == 'q')//fechar janela
    {
        endwin();
        exit(0);
    }
    if (c == 'B')//seta bra baixo;
    {
        mvprintw(18, 20, "|");
        mvprintw(19, 20, "v");
        if ((*linha_inicial) < QTDPIDS)
        {
            (*linha_inicial)++;
        }
    }
    if (c == 'A')//seta pra cima
    {
        
        mvprintw(18, 20, "^");
        mvprintw(19, 20, "|");

        if ((*linha_inicial) >= 1)
        {
            (*linha_inicial)--;
        }
    }
    if (c == 'c')//comentarios repetidos em c,p,u,t
    {   
        //Apagar uma cor de cima e acender as outras
        attron(COLOR_PAIR(1));
        move(0, 0);
        int j;
        for (j = 0; j < 80; j++)
        {
            printw(" ");
        }
        printupside();
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(0));
        mvprintw(0, 40, "%%CPU");
        attroff(COLOR_PAIR(0));
        //alterar indice da função pra ordenação
        compara_func = 0;
        (*linha_inicial) = 0;
    }
    if (c == 'p')
    {
        attron(COLOR_PAIR(1));
        move(0, 0);
        int j;
        for (j = 0; j < 80; j++)
        {
            printw(" ");
        }
        printupside();
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(0));
        mvprintw(0, 0, "PID");
        attroff(COLOR_PAIR(0));
        compara_func = 1;
        (*linha_inicial) = 0;
    }
    if (c == 'u')
    {
        attron(COLOR_PAIR(1));
        move(0, 0);
        int j;
        for (j = 0; j < 80; j++)
        {
            printw(" ");
        }
        printupside();
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(0));
        mvprintw(0, 10, "USER");
        attroff(COLOR_PAIR(0));
        compara_func = 2;
        (*linha_inicial) = 0;
    }
    if (c == 't')
    {
        attron(COLOR_PAIR(1));
        move(0, 0);
        int j;
        for (j = 0; j < 80; j++)
        {
            printw(" ");
        }
        printupside();
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(0));
        mvprintw(0, 50, "TEMPO");
        attroff(COLOR_PAIR(0));
        compara_func = 3;
        (*linha_inicial) = 0;
    }
    if (c == 'l')//Ler Conteudo digitado na tela
    {
        int i=0;
        mvprintw(24, 15, "...                        ");
        attron(COLOR_PAIR(1));
        mvprintw(24, 40, "pressione enter or backspace");
        attroff(COLOR_PAIR(1));
        refresh();
        curs_set(1);
        move(24, 15);
        for (i = 0;;)
        {
            char a = getch();
            if (a == '\n')//ler enter
            {
                mvprintw(24, 40, "                               ");
                curs_set(0);
                break;
            }
            if (a == 127)//ler backspace
            {
                mvprintw(24, 15, "                              ");
                move(24, 15);
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
    if (c == 'k')//matar processo selecionado
		{

			attron(COLOR_PAIR(1));
			mvprintw(22, 30, "Matar(%s)? pressione k ou n", Dados[(*linha_inicial)].COMMAND);
			refresh();
			attroff(COLOR_PAIR(1));
			timeout(10000);//esperar por um resposta por 5 segundos
			int k = getch();
			if (k == 'n' || k == -1)//apagar aviso
			{
				
                mvprintw(22, 30, "                                        ");
				refresh();
			}
			else if (k == 'k')//matar processo
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
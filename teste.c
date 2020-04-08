#include <stdio.h>
#include <ncurses.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    initscr();
    int i=0;
    for(i=0;i<5;++i)
    {
        pid_t pid=fork();
    
        if(pid==0){
        move(i,0);    
        printw("%d",i);
        }
        else
        {
            wait(NULL);
        }
        
        
    }
    getch();
    endwin(); 



}
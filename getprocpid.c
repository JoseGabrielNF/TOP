#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
void getprocpid(int PIDS[5000],int *QTDPIDS)
{
    DIR *dir;
    struct dirent *lsdir;
     
    dir = opendir("/proc");
    (*QTDPIDS)=0;
    int read=0;
    /* print all the files and directories within directory */
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
      //  printf ("%s\n", lsdir->d_name);
        if(strcmp(lsdir->d_name,"1")==0)
        {
          read=1;
        }
        if(read)
        {
         PIDS[(*QTDPIDS)]=atoi(lsdir->d_name);
          (*QTDPIDS)++;

        }
    }

    closedir(dir);

    return ;

}
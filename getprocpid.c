#include <mytop.h>

void getprocpid(int PIDS[5000],int *QTDPIDS)
{
    DIR *dir;
    struct dirent *lsdir;
     
    dir = opendir("/proc");
    (*QTDPIDS)=0;
    int read=0;
    if(dir==NULL)
    {
       perror("Error opening file getprocpid");
    }else{
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        if(strcmp(lsdir->d_name,"1")==0)//detecta o primeiro numero e começa escanear os diretórios
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
    }
    return ;

}
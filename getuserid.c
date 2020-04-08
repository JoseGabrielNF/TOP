#include <stdio.h>

void getuserid(char usr[100][100], char id[100][100], char id2[100][100])
{
    FILE *arq;
    char mystring[10000];
    //Abre arquivo passwd
    arq = fopen("/etc/passwd", "r");

    //Verifica se tem erro ao abrir
    if (arq == NULL)
    {
        perror("Error opening file");
    }
    else
    {
    //O arquivo passwd tem o formato usuário:x:id:id2:

        int indice = 0;
        while (fgets(mystring, 1000, arq) != NULL)
        {
            int i = 0;
            int k = 0;
            int j = 0;
            int contagem = 0;
            for (i = 0; mystring[i] != '\0'; i++)
            {
                // A variavel contagem conta quantas vezes aparece o simbolo :
                if (mystring[i] == ':')
                {
                    contagem++;
                    continue;
                }
                 // Se não aparecer nada é o usuário
                if (contagem == 0)
                {

                    usr[indice][i] = mystring[i];
                    usr[indice][i + 1] = '\0';
                }
                 // Se aparecer 2 ":" então le o primeiro id
                if (contagem == 2)
                {
                    id[indice][k] = mystring[i];
                    id[indice][k + 1] = '\0';
                    k++;
                }
                // Se aparecer 3 ":" então le o segundo id
                if (contagem == 3)
                {
                    id2[indice][j] = mystring[i];
                    id2[indice][j + 1] = '\0';
                    j++;
                }
                // Se aparecer 4 ":" então sai do laço e vai pra proxima linha do arquivo
                if (contagem == 4)
                {
                    break;
                }
            }
            indice++;
            // o final vetor usuário é marcado por um 7 como referencia;
            usr[indice][0] = '7';
        }

        fclose(arq);
    }
}

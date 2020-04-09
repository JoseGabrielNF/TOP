#include <mytop.h>

int compara(const void *p1, const void *p2)
{
	const struct mytop *elem1 = p1;
	const struct mytop *elem2 = p2;

	if (compara_func == 0)//compara cpu
	{
		if (elem1->CPU > elem2->CPU)
			return -1;
		else if (elem1->CPU < elem2->CPU)
			return 1;
		else
			return 0;
	}
	else if (compara_func == 1)//compara pid
	{
		if (atoi(elem1->pid) < atoi(elem2->pid))
			return -1;
		else if (atoi(elem1->pid) > atoi(elem2->pid))
			return 1;
		else
			return 0;
	}
	else if (compara_func == 2)//compara usuario
	{
		return strcmp(elem1->USER, elem2->USER);
	}
	else if (compara_func == 3)//compara tempo
	{
		if (elem1->TIME > elem2->TIME)
			return -1;
		else if (elem1->TIME < elem2->TIME)
			return 1;
		else
			return 0;
	}
	else if (compara_func == 4)//compara os elementos do vetores com as palavras
	{
		if(strcmp(elem1->COMMAND,word))
		{
			return 1;
		}
		else
		{
			return -1;
		}		
	}

  return 0;

}

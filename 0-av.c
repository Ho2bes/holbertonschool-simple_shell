#include <stdio.h>

int main(int ac, char **av)
{
	int i = 0;
	int j = 0;
	if(av == NULL)
		return 0;

	while (av[i] != NULL) 
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			putchar(av[i][j]);
			j++;
        }
		putchar('\n');
		i++;
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

/**
 *
 *
 *
 **/

int main()
{
        char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");
		read = getline(&line, &len, stdin);
		printf("%s", line);
		printf("%ld\n", read - 1);
	}
}

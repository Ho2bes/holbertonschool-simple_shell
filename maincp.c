#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 *
 *
 *
 *
 *
 **/

int main()
{
       	char *line = NULL;
        size_t len = 0;
        ssize_t read;
		char* token;
		const char delim[] = " ";

        while (1)
        {
                printf("$ ");
                read = getline(&line, &len, stdin);
                printf("%s", line);
                printf("%ld\n", read - 1);

		        /*Obtenez le premier token*/
        		token = strtok(line, delim);

        		/*Parcourez les tokens restants*/
        		while (token != NULL)
                        {
                                printf("%s\n", token);
                                /*Obtenez le prochain token*/
                                token = strtok(NULL, delim);
                        }
        }
}

/*int error_filter(char *str)*/

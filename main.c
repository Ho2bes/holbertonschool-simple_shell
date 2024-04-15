#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 **/

void array_cut(char *str, unsigned int len)
{
        const char delim[] = " ,.!?:/\n\t|*-_=;";
        char* token;

        // Obtenez le premier token
        token = strtok(str, delim);

        // Parcourez les tokens restants
        while (token != NULL)
        {
                printf("%s\n", token);
                // Obtenez le prochain token
                token = strtok(NULL, delim);
        }
}

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

                array_cut(line, read -1);
        }
}

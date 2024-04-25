#include "willson.h"
/**
 * tokenize_command - Tokenize a command string into an array of tokens
 * @command: The command string to tokenize
 *
 * Return: An array of tokens
 */
char **tokenize_command(char *command)
{
    int i = 0;
    char *token;
    char **tokens = malloc(sizeof(char *) * 256);
    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    token = strtok(command, " \n\t");
    while (token != NULL)
    {
        tokens[i] = strdup(token);
        if (tokens[i] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, " \n\t");
    }
    tokens[i] = NULL;
    return (tokens);
}

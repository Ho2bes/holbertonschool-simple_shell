#include "willson.h"

/**
 * tokenize_command - Tokenize a command string into an array of tokens
 * @command: The command string to tokenize
 *
 * Return: An array of tokens
 */

char **tokenize_command(char *command)
{
	char **tokens = malloc(sizeof(char *) * 256);
	/* Dynamically allocate memory for tokens */
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	char *saveptr;
	char *token = strtok_r(command, " ", &saveptr);
	/* Tokenize the command string */
	int i = 0;
	/* Initialize index of the tokens array */
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		/* Duplicate the token */
		if (tokens[i] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
		/* Move to the next token */
		token = strtok_r(NULL, " ", &saveptr);
		/* Get the next token */
	}
	tokens[i] = NULL;
	/* Mark the end of tokens */
	return (tokens);
	/* Return the tokens array */
}

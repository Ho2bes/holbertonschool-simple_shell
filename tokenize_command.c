#include "willson.h"

/**
 * tokenize_command - Tokenize a command string into an array of tokens
 * @command: The command string to tokenize
 *
 * Return: An array of tokens
 */

char **tokenize_command(char *command)
{
	char *saveptr;/* Dynamically allocate memory for tokens */
	int i = 0;
	char *token;
	char **tokens = malloc(sizeof(char *) * 256);

	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok_r(command, " ", &saveptr);
	/* Tokenize the command string */
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

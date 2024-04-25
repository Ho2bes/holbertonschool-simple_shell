#include "willson.h"

/**
 * main - Entry point of the program
 * @argc: Number of arguments passed to the program
 * @argv: Array of pointers to the arguments
 * @env: Array of pointers to the environment variables
 *
 * Return: Always 0
 */

int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t bufsize = 0;
	ssize_t nb;
	int status = 0;
	(void) argc;
	(void) argv;

	while (1)
	{
		/* If STDIN is a terminal, display the prompt */
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
			fflush(stdout);
		}
		nb = getline(&input, &bufsize, stdin);
		if (nb == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (input)
				free(input);
			exit(status);
			/*break;*/
			/* Exit the loop if getline fails */
		}
		if (nb > 1 && input[nb - 1] == '\n')
		{
			input[nb - 1] = '\0';
		}
		if (strcmp(input, "exit") == 0)
		{
			break;
			/* Exit the loop if the command is "exit" */
		}
		status = execute_command(input, env);
	}
	free(input);
	/* Check if input is NULL before freeing it */
	return (0);
}

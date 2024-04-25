#include "willson.h"
/**
 * execute_command - execute command from input
 * @command: input command from the main
 * @env: environment variables
 * Return: Void
 **/
int execute_command(char *command, char **env)/*argv[0], pr recup ./hsh*/
{
	/* Tokenizing the command */
	char **command_tokens = tokenize_command(command);
	char *command_path = find_command_path(command_tokens[0]);
	/* Finding the full path of the command */
	int i, status;
	pid_t pid; /* Declaration moved outside of the if-else block*/

	if (command_path == NULL)
	{ /* If command not found, free memory and return */
		for (i = 0; command_tokens[i] != NULL; i++)
			free(command_tokens[i]);
		free(command_tokens);
		return (127);
	}
	pid = fork(); /* Creating a child process */
	if (pid == -1)
	{
		perror("erreur fork");
		exit(-1);
	}
	else if (pid == 0)
	{ /* Child process */
		if (execve(command_path, command_tokens, env) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", command_tokens[0]);
			printf(" \n");
			exit(127);
		}
	}
	else
	{ /* Parent process and Freeing allocated memory */
		for (i = 0; command_tokens[i] != NULL; i++)
			free(command_tokens[i]);
		free(command_tokens);
		free(command_path);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

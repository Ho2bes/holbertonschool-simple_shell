#include "willson.h"
/**
 * execute_command - execute command from input
 * @command: input command from the main
 * @env: environment variables
 * Return: Void
 **/
void execute_command(char *command, char **env)
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
		return;
	}
	pid = fork(); /* Creating a child process */
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{ /* Child process */
		if (execve(command_path, command_tokens, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
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
}

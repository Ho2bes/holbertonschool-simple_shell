#include "willson.h"

/**
 * find_command_path - find the path of a command
 * @command: input of command
 * Return: string of the path
 */
char *find_command_path(const char *command)
{
	char *search_path = strdup(getenv("PATH"));
	char *token = strtok(search_path, ":");
	char full_path[PATH_MAX];
	char *result = NULL;
	struct stat st;

	if (command[0] == '/')
	{
		if (stat(command, &st) == 0 && st.st_mode & S_IXUSR)
		{
			free(search_path); /* Libérer la mémoire avant de retou */
			return (strdup(command));
		}
		else
		{
			fprintf(stderr, "/hsh: 1: %s: not found\n", command);
			free(search_path); /* Libérer la mémoire avant de retour*/
			return (NULL);
		}
	}

	while (token != NULL)
	{
		sprintf(full_path, "%s/%s", token, command);
		if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR)
		{
			result = strdup(full_path);
			break;
		}
		token = strtok(NULL, ":");
	}

	free(search_path); /*Libérer la mémoire avant de retou */
	if (result == NULL)
		fprintf(stderr, "./hsh: 1: %s: not found\n", command);
	return (result);
}

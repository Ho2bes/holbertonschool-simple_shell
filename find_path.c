#include "willson.h"

/**
 * find_command_path - find the path of a command
 * @command: input of command
 * @env: environment variables
 * Return: string of the path
 */
char *find_command_path(const char *command)
{
	char *search_path = strdup(getenv("PATH"));
	/* Retrieve the PATH environment variable */
	char *token = strtok(search_path, ":");
	/* Split the environment variable into tokens */
	char full_path[PATH_MAX]; /* Use PATH_MAX to define the max size of path */
	char *result = NULL; /* Declare the result initialized to NULL */
	struct stat st;
	/* Check if command contains an absolute path */
	if (command[0] == '/')
	{ /* Check if the file exists and is executable */
		if (stat(command, &st) == 0 && st.st_mode & S_IXUSR)
		{
			return strdup(command); /* Return the found full path */
		}
		else
		{
			fprintf(stderr, "Error: Command '%s' not found\n", command);
			return NULL;
		}
	}
	while (token != NULL)/* Traverse the directories in the PATH */
	{ /* Construct the full path of the command */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		/* Check if the file exists and is executable */
		if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR)
		{
			result = strdup(full_path);
			/* Duplicate the found full path */
			break;
		}
		token = strtok(NULL, ":");
		/* Move to the next directory in the PATH */
	}
	/* If the command was not found, display an error */
	if (result == NULL)
		fprintf(stderr, "Error: Command '%s' not found or not executable\n", command);
	free(search_path);
	return result; /* Return the full path of the command */
}

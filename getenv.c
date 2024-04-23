#include "willson.h"

/**
 * getenv_var - Get the value of a specified environment variable.
 * @var_name: The name of the environment variable to search for.
 * @env: The array of environment variables.
 *
 * Return: A pointer to the value of the environment variable if found,
 *         otherwise NULL.
 */

char *getenv_var(const char *var_name, char **env)
{
	int i;
	/* Loop index */

	/* Calculate the length of the variable name */
	size_t var_name_len = strlen(var_name);

	/* Iterate through the environment variables array */
	for (i = 0; env[i]; i++)
	{
		/* Check if the current environment variable matches the specified name */
		if (strncmp(env[i], var_name, var_name_len) == 0
				&& env[i][var_name_len] == '=')
		{
			/* Return a pointer to the value of the environment variable */
			return (&env[i][var_name_len + 1]);
		}
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}

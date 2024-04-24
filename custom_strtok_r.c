#include "willson.h"

/**
 * custom_strtok_r - RTFM
 * @command: the command who was in the input
 * @delim: what cut the command
 * @array_str: array who stock the tokenning command
 * Return: token
 **/

char *custom_strtok_r(char *command, const char *delim, char **array_str)
{
	char *token;

	/*If saveptr is NULL or points to the end of string, return NULL*/
	if (*array_str == NULL || **array_str == '\0')
	{
		return (NULL);
	}
	/*If str is not NULL, set saveptr to str*/
	if (command != NULL)
	{
		*array_str = command;
	}

	/*Skip leading delimiters*/
	while (**array_str != '\0' && strchr(delim, **array_str) != NULL)
	{
		(*array_str)++;
	}
	token = *array_str;
	/*If end of string is reached, set saveptr to NULL and return token*/
	if (**array_str == '\0')
	{
		*array_str = NULL;
		return (token);
	}

	/*Find the end of the token*/
	while (**array_str != '\0' && strchr(delim, **array_str) == NULL)
		(*array_str)++;

	/*If not end of string, terminate token and move saveptr*/
	if (**array_str != '\0')
	{
		**array_str = '\0';
		(*array_str)++;
	}
	return (token);
}

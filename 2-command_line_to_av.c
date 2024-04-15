#include <stdio.h>
#include <stdlib.h>

void main ()
{
	char str[];
	const char delim[] = " ,.!?:/\n\t|*-_=;" // Les délimiteurs sont l'espace, la virgule et le point d'exclamatio
	char* token;

	// Obtenez le premier token
	token = strtok(str, delim);

	// Parcourez les tokens restants
	while (token != NULL)
	{
		printf("%s\n", token);
		// Obtenez le prochain token
		token = strtok(NULL, delim);
	}
	return 0;
}

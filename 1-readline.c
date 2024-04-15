#include <stdio.h>

int main(int argc, char *argv[]) 
{
	if (argc < 2)
	{
		printf("Usage: %s <command>\n", argv[0]);
		return 1;
	}
	// Imprime "$ " pour indiquer que l'interpréteur de commandes est prêt
	printf("$ ");
	// Imprime la commande passée en argument sur la ligne suivante
	printf("%s\n", argv[1]);
	return 0;
}

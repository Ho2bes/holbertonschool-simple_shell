// Déclaration du prototype de la fonction getline personnalisée

void custom_getline(char **lineptr, size_t *bufsize, int *status);
int main()
{
	char *user_input = NULL; // Pointeur pour stocker la ligne saisie par l'utilisateur
	size_t buffer_size = 0; // Taille initiale du tampon allou�
	int read_status = 0; // Statut de la lecture de la ligne
			     // Appel de la fonction custom_getline pour lire une ligne depuis l'entrée standar
	custom_getline(&user_input, &buffer_size, &read_status);
	// Vérification du statut de lecture
	
	if (read_status == -1) { // En cas d'erreur de lecture
		fprintf(stderr, "Erreur lors de la lecture de la ligne\n");
		// Gérer l'erreur ici, par exemple, libérer la mémoire allo
		free(user_input);
		return EXIT_FAILURE; // Quitter le programme avec un code d'erreur
	}
	
	printf("Vous avez saisi: %s\n", user_input); // Afficher la saisie de l'utilisateur
	free(user_input); // Libérer la mémoire allouée pour la saisie de l'utilisar
	
	return EXIT_SUCCESS; // Quitter le programme avec un code de succè
}

// Définition de la fonction getline personnalisée

void custom_getline(char **lineptr, size_t *bufsize, int *status)
{
	ssize_t chars_read; // Nombre de caractères lu
			    
	// Lire une ligne depuis l'entrée standar
	chars_read = getline(lineptr, bufsize, stdin);

	// Vérifier s'il y a eu une erreur lors de la lectur
	if (chars_read == -1)
	{
		*status = -1; // Affecter -1 au statut en cas d'erreur
	}
}

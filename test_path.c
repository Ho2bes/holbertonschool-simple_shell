#include "willson.h"
#include "custom_function.c"
#include "tokenning.c"

char *_getenv(char *name, char **env)
{
	int i, j;

	for (i = 0; env[i]; i++)
	{
		for (j = 0; env[i][j]; j++)
		{
			if (env[i][j] == name[j])
				continue;
			else if (env[i][j] == '=' && name[j] == '\0')
			{
				return (&env[i][j + 1]);
			}
			else
				break;
		}
	}
	return (NULL);
}

char* cmd_path(char **array_tok[0], char **env) {
    char *path = _getenv("PATH", env);
    char *token = strtok(path, ":");
    char* result = NULL;
    char full_path[256];
    char* args[] = {command, NULL}; // Arguments pour execve

    if (access(command, X_OK) == 0)
    {
        return (command);
    }

    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(path, X_OK) == 0) {
            // Command found, return its full path
            printf("%s", path);
            printf("%s", full_path);
            result = strdup(full_path);
            break;
        }
        token = strtok(NULL, ":");
    }
    return result;
}


// Fonction pour exécuter une commande donnée en tant que sous-processus
void execute_command(char* command, char **env)
{
    char** array_tok = tokenning(command);
    char* path = cmd_path(array_tok[0], env); // Utiliser le premier élément de array_tok comme commande
    if (path == NULL) {
        printf("Erreur: Commande introuvable\n");
        return;
    }
    if (fork() == 0)
    {
        if (execve(array_tok[0], array_tok, env) == -1) // Utiliser execve correctement avec les arguments de la commande
        {
            perror(path); // Utiliser le chemin complet de la commande en cas d'erreur
            exit(-1);
        }
    }
}

int main(int argc, char **argv,char **env) {
	char *input = NULL;
    size_t bufsize = 0;
    ssize_t read;
	(void) argc;
    // Vérifier si le shell est en mode non interactif

	{
        printf("$ ");
        read = getline(&input, &bufsize, stdin);
        // Lire et exécuter les commandes de l'entrée standard
        if (read != -1) {
            execute_command(input, env); // Exécuter la commande
        }
        if (read == -1) { // Gérer les erreurs lors de la lecture de l'entrée standard
            perror("getline");
            exit(EXIT_FAILURE);
        }
        return 0;
    }
    // Boucle pour le mode interactif
    while (1) {
		if (!isatty(STDIN_FILENO))
			printf("$ "); // Afficher un prompt pour l'utilisateur
        /*fflush(stdout); Forcer l'affichage du prompt*/
        // Lire l'entrée de l'utilisateur depuis stdin
        if ((read = getline(&input, &bufsize, stdin)) == -1) {
            perror("getline"); // Gérer les erreurs de lecture
            exit(EXIT_FAILURE);
        }

        if (read == 1 && input[0] == '\n') { // Vérifier si l'entrée est vide (seulement la nouvelle ligne)
            continue; // Ignorer et revenir à la prochaine itération
        }
        input[read - 1] = '\0'; // Supprimer le caractère de nouvelle ligne
        if (strcmp(input, "exit") == 0) { // Vérifier la commande "exit"
            break; // Sortir de la boucle si la commande est "exit"
        }
        execute_command(input, env); // Exécuter la commande
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
 /*Pour PATH_MAX*/

#define PATH_MAX 1024
/*Fonction pour obtenir la valeur d'une variable d'environnement*/
char* getenv_var(const char *var_name, char **env) {
    int i;
    size_t var_name_len = strlen(var_name);
    for (i = 0; env[i]; i++) {
        if (strncmp(env[i], var_name, var_name_len) == 0 && env[i][var_name_len] == '=') {
            return &env[i][var_name_len + 1];
        }
    }
    return NULL;
}
/*Fonction pour trouver le chemin complet d'une commande*/
char* find_command_path(const char *command, char **env) {
    /*Vérifie si la commande spécifiée contient déjà un chemin absolu*/
    if (command[0] == '/') {
        /*Vérifie si le fichier existe et est exécutable*/
        struct stat st;
        if (stat(command, &st) == 0 && st.st_mode & S_IXUSR) {
            return strdup(command); /*Retourne le chemin complet trouvé*/
        } else {
            fprintf(stderr, "Erreur : Commande '%s' non trouvée ou non exécutable\n", command);
            return NULL;
        }
    }
    char *search_path = strdup(getenv_var("PATH", env)); /*Récupération de la variable d'environnement PATH*/
	char *token = strtok(search_path, ":"); /*Découpage de la variable d'environnement en tokens*/
    char full_path[PATH_MAX]; /*Utilisation de PATH_MAX pour définir la taille maximale du chemin*/
    char* result = NULL; /*Déclaration du résultat initialisé à NULL*/
    /*Parcours des répertoires dans le PATH*/
    while (token != NULL) {
        /*Construction du chemin complet de la commande*/
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        struct stat st;
        /*Vérification si le fichier existe et est exécutable*/
        if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
            result = strdup(full_path); /*Duplication du chemin complet trouvé*/
            break;
        }
        token = strtok(NULL, ":"); /*Passage au prochain répertoire dans le PATH*/
    }
    /*Si la commande n'a pas été trouvée, affichage d'une erreur*/
    if (result == NULL) {
        fprintf(stderr, "Erreur : Commande '%s' non trouvée ou non exécutable\n", command);
    }
	free(search_path);
    return result; /*Retour du chemin complet de la commande*/
}
/*Fonction pour découper une commande en tokens*/
char** tokenize_command(char *command) {
    char **tokens = malloc(sizeof(char*) * 256); /*Allocation dynamique de mémoire pour les tokens*/
    if (tokens == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char *saveptr;
    char *token = strtok_r(command, " ", &saveptr); /*Découpage de la commande en tokens*/
    int i = 0; /*Initialisation de l'indice du tableau de tokens*/
    while (token != NULL) {
        tokens[i] = strdup(token); /*Duplication du token*/
        if (tokens[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++; /*Passage au prochain token*/
        token = strtok_r(NULL, " ", &saveptr); /*Obtention du token suivant*/
    }
    tokens[i] = NULL; /*Marquage de la fin des tokens*/
    return tokens; /*Retour du tableau de tokens*/
}
/*Fonction pour exécuter une commande*/
void execute_command(char* command, char **env) {
    char** command_tokens = tokenize_command(command); /*Découpage de la commande en tokens*/
    char* command_path = find_command_path(command_tokens[0], env); /*Recherche du chemin complet de la commande*/
    if (command_path == NULL) {
        /*Si la commande n'a pas été trouvée, libération de la mémoire et retour*/
        for (int i = 0; command_tokens[i] != NULL; i++) {
            free(command_tokens[i]);
        }
        free(command_tokens);
        return;
    }
    pid_t pid = fork(); /*Création d'un processus fils*/
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /*Processus fils*/
        if (execve(command_path, command_tokens, env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        /*Processus parent*/
        /*Libération de la mémoire allouée*/
        for (int i = 0; command_tokens[i] != NULL; i++) {
            free(command_tokens[i]);
        }
        free(command_tokens);
        free(command_path);
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}
int main(int argc, char **argv, char **env) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t nb;
    while (1) {
        /*Si STDIN est un terminal, affiche le prompt*/
        if (isatty(STDIN_FILENO)) {
            printf("$ ");
            fflush(stdout);
        }
        if ((nb = getline(&input, &bufsize, stdin)) == -1) {
            break; /*Quitte la boucle si getline échoue*/
        }
        if (nb > 1 && input[nb - 1] == '\n') {
            input[nb - 1] = '\0';
        }
        if (strcmp(input, "exit") == 0) {
            break; /*Quitte la boucle si la commande est "exit"*/
        }
        execute_command(input, env);
    }
    free(input); /*Vérification si input est NULL avant de le libérer*/
    return 0;
}

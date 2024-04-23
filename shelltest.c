#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
// Fonction pour obtenir la valeur d'une variable d'environnement
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
// Fonction pour trouver le chemin complet d'une commande
char* find_command_path(const char *command, char **env) {
    char *search_path = getenv_var("PATH", env);
    char *token = strtok(search_path, ":");
    char full_path[256];
    char* result = NULL;
    while (token != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        struct stat st;
        if (stat(full_path, &st) == 0 && st.st_mode & S_IXUSR) {
            result = strdup(full_path);
            break;
        }
        token = strtok(NULL, ":");
    }
    if (result == NULL) {
        fprintf(stderr, "Erreur : Commande '%s' non trouvée ou non exécutable\n", command);
    }
    return result;
}
// Fonction pour découper une commande en tokens
char** tokenize_command(char *command) {
    char **tokens = malloc(sizeof(char*) * 256);
    if (tokens == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    char *token = strtok(command, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i] = strdup(token);
        if (tokens[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        i++;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}
// Fonction pour exécuter une commande
void execute_command(char* command, char **env) {
    char** command_tokens = tokenize_command(command);
    char* command_path = find_command_path(command_tokens[0], env);
    if (command_path == NULL) {
        for (int i = 0; command_tokens[i] != NULL; i++) {
            free(command_tokens[i]);
        }
        free(command_tokens);
        return;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execve(command_path, command_tokens, env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
    for (int i = 0; command_tokens[i] != NULL; i++) {
        free(command_tokens[i]);
    }
    free(command_tokens);
    free(command_path);
}
int main(int argc, char **argv, char **env) {
    char *input = NULL;
    size_t bufsize = 0;
    ssize_t nb;
    while (1) {
        // Si STDIN est un terminal, affiche le prompt
        if (isatty(STDIN_FILENO)) {
            printf("$ ");
            fflush(stdout);
        }
        if ((nb = getline(&input, &bufsize, stdin)) == -1) {
            break; // Quitte la boucle si getline échoue
        }
        if (nb > 1 && input[nb - 1] == '\n') {
            input[nb - 1] = '\0';
        }
        if (strcmp(input, "exit") == 0) {
            break; // Quitte la boucle si la commande est "exit"
        }
        execute_command(input, env);
    }
    free(input);
    return 0;
}

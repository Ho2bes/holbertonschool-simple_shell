#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        // Afficher le prompt
        printf("#cisfun$ ");

        // Lire la commande de l'utilisateur
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Sortir de la boucle si Ctrl+C est pressé ou si fgets échoue
        }

        // Supprimer le saut de ligne à la fin de la commande
        command[strcspn(command, "\n")] = '\0';

        // Fork pour créer un nouveau processus
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Processus enfant : exécuter la commande
            if (execlp(command, command, (char *)NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Processus parent : attendre la fin du processus enfant
            int status;
            wait(&status);
        }
    }

    return 0;
}

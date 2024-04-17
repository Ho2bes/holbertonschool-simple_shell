#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // Définition de la longueur maximale d'une commande

int main() {
    char user_command[MAX_COMMAND_LENGTH]; // Déclaration d'une variable pour stocker la commande de l'utilisateur

    while (1) { // Boucle infinie pour l'exécution continue du shell
        // Afficher le prompt
        printf("#$ ");

        // Lire la commande de l'utilisateur
        if (fgets(user_command, sizeof(user_command), stdin) == NULL) {
            break; // Sortir de la boucle si Ctrl+C est pressé ou si fgets échoue
        }

        // Supprimer le saut de ligne à la fin de la commande
        user_command[strcspn(user_command, "\n")] = '\0';

        // Fork pour créer un nouveau processus
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork"); // Afficher un message d'erreur si le fork échoue
            exit(EXIT_FAILURE); // Quitter le programme avec un code d'erreur
        } else if (child_pid == 0) {
            // Processus enfant : exécuter la commande
            if (execlp(user_command, user_command, (char *)NULL) == -1) {
                perror("execlp"); // Afficher un message d'erreur si execlp échoue
                exit(EXIT_FAILURE); // Quitter le processus enfant avec un code d'erreur
            }
        } else {
            // Processus parent : attendre la fin du processus enfant
            int status;
            wait(&status); // Attendre que le processus enfant se termine
        }
    }

    return 0; // Fin du programme
}

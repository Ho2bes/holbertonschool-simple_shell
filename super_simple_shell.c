#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100 // Définition de la longueur maximale d'une commande

int main() {
    char *user_command = NULL; // Utilisation d'un pointeur de type char pour stocker la commande de l'utilisateur
    size_t command_buffer_size = 0; // Taille initiale du tampon pour getline

    while (1) { // Boucle infinie pour l'exécution continue du shell
        // Afficher le prompt
        printf("#$ ");

        // Lire la commande de l'utilisateur avec getline
        if (getline(&user_command, &command_buffer_size, stdin) == -1) {
            break; // Sortir de la boucle si Ctrl+C est pressé ou si getline échoue
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

    free(user_command); // Libérer la mémoire allouée par getline
    return 0; // Fin du programme
}

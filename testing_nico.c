#include "willson.h"
#include "custom_function.c"

#define MAX_INPUT_SIZE 1024
// Fonction pour exécuter une commande donnée en tant que sous-processus
void execute_command(char *input) {
    pid_t pid;
    char *command;
    char *args[2];
    pid = fork(); // Créer un nouveau processus enfant
    if (pid == -1) { // Vérifier les erreurs lors de la création du processus
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) { // Code pour le processus enfant
        command = strtok(input, " "); // Séparer la commande et ses arguments
        args[0] = command;
        args[1] = NULL; // Marquer la fin des arguments avec NULL
        if (execvp(args[0], args) == -1) { // Exécuter la commande
            perror("execvp"); // Gérer les erreurs d'exécution
            _exit(EXIT_FAILURE); // Terminer le processus enfant en cas d'erreur
        }
    } else { // Code pour le processus parent
        wait(NULL); // Attendre que le processus enfant se termine
    }
}
int main(void) {
    char input[MAX_INPUT_SIZE];
    ssize_t read;
    // Vérifier si le shell est en mode non interactif
    if (!isatty(STDIN_FILENO)) {
        // Lire et exécuter les commandes de l'entrée standard
        while ((read = getline(&input, &MAX_INPUT_SIZE, stdin)) != -1) {
            execute_command(input); // Exécuter la commande
        }
        if (read == -1) { // Gérer les erreurs lors de la lecture de l'entrée standard
            perror("getline");
            exit(EXIT_FAILURE);
        }
        return 0;
    }
    // Boucle pour le mode interactif
    while (1) {
        printf("($) "); // Afficher un prompt pour l'utilisateur
        fflush(stdout); // Forcer l'affichage du prompt
        // Lire l'entrée de l'utilisateur depuis stdin
        if ((read = getline(&input, &MAX_INPUT_SIZE, stdin)) == -1) {
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
        execute_command(input); // Exécuter la commande
    }
    return 0;
}

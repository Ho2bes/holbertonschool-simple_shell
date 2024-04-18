#include "willson.h"

void cmd_path(char **argv) {
    char *path = getenv("PATH");
    char *token = strtok(path, ":");
    while (token != NULL) {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "%s/%s", token, argv[1]);
        if (access(filepath, F_OK) != -1) {
            printf("Le fichier %s a été trouvé dans le répertoire : %s\n", argv[1], token);
            printf("Chemin complet du fichier : %s\n", filepath);
            break;
        }
        token = strtok(NULL, ":");
    }
}

int main() {
    char *user_input = NULL;
    size_t buffer_size = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        read = getline(&user_input, &buffer_size, stdin);

        if (read == -1) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne\n");
            free(user_input);
            return EXIT_FAILURE;
        }

        char *argv[2];
        argv[0] = "./a.out"; // Nom du programme
        argv[1] = strtok(user_input, " \n"); // Premier argument

        cmd_path(argv);
		free(user_input);
    }


    return EXIT_SUCCESS;
}

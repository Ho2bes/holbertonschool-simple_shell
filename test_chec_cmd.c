#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour vérifier si la commande 'ls' est exécutable
int check_ls_executable() {
    if(system("ls --version") == 0) {
        return 1; // La commande 'ls' est exécutable
    } else {
        return 0; // La commande 'ls' n'est pas exécutable
    }
}

int main() {
    char* path = getenv("PATH");
    char* ls_path = "/bin/ls"; // Chemin par défaut de la commande 'ls'

    if(path != NULL) {
        if(strstr(path, "/bin") == NULL) {
            printf("Le répertoire /bin n'est pas inclus dans le PATH. Veuillez le rajouter.\n");
        } else {
            if(check_ls_executable()) {
                printf("La commande 'ls' est exécutable.\n");
            } else {
                printf("La commande 'ls' n'est pas exécutable. Veuillez vérifier les autorisations.\n");
            }
        }
    } else {
        printf("La variable PATH n'est pas définie. Veuillez la configurer correctement.\n");
    }

    return 0;
}

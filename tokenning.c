#include "willson.h"

char** tokenning(char *input) {

    char *token = strtok(input, " \n\t"); // Découpage de l'entrée en tokens
    int count = 0;
    char **array_tok = (char **)malloc(sizeof(char *)); // Allocation initiale d'un tableau de pointeurs de chaînes de caractères

    while (token != NULL) {
        array_tok = (char **)myRealloc(array_tok, (count + 1) * sizeof(char *)); // Réallocation du tableau pour ajouter un nouveau token
        array_tok[count] = (char *)malloc(strlen(token) + 1); // Allocation d'espace pour stocker le token
        strcpy(array_tok[count], token); // Copie du token dans le tableau
        count++;
        token = strtok(NULL, " \n\t"); // Passage au token suivant
    }

    // Affichage des tokens stockés dans le tableau
    for (int i = 0; i < count; i++) {
        printf("Token %d: %s\n", i, array_tok[i]);
        free(array_tok[i]); // Libération de la mémoire allouée pour chaque token
    }

    free(array_tok); // Libération du tableau de pointeurs
    return array_tok;
}

void* myRealloc(void* ptr, size_t newSize) {
    void* newPtr = malloc(newSize);
    if (newPtr == NULL) {
        return NULL; // Gestion de l'échec de l'allocation
    }

    // Copie des données du bloc existant vers le nouveau bloc
    char* src = (char*)ptr;
    char* dest = (char*)newPtr;
    for (size_t i = 0; i < newSize; i++) {
        dest[i] = src[i];
    }

    free(ptr); // Libération de l'ancien bloc de mémoire

    return newPtr;
}

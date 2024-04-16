#include <stdio.h>

int main() {
    int num;
    FILE *fptr;

    fptr = fopen("fichier.txt", "r");
    if (fptr == NULL) {
        printf("Erreur lors de l'ouverture du fichier.");
        return 1;
    }

    while (fscanf(fptr, "%d", &num) != EOF) {
        printf("%d\n", num);
    }

    fclose(fptr);
    return 0;
}

/**
*Dans cet exemple, le programme ouvre un fichier "fichier.txt" en mode lecture.
*Ensuite, il lit les entiers du fichier un par un à l'aide de la fonction fscanf dans une boucle while.
*La boucle se poursuit tant que la fonction fscanf ne renvoie pas EOF, indiquant la fin du fichier.
* Une fois que EOF est détecté, la boucle s'arrête et le fichier est fermé.
*
*En résumé, gérer la condition EOF en langage C permet au programme de lire un fichier
* jusqu'à la fin de manière appropriée et de prendre des mesures en conséquence.
**/

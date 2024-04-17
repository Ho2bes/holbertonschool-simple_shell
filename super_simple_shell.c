#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void display_arguments(int ac, char** av)
{
	// Déclaration de variables pour l'itératioa  travers les argumennts
	int i = 0;  // indice pour parcourir les arguments principaux
	int j = 0;  // indice pour parcourir chaque caractère dans un argument

	// Vérifier si aucun argument n'a étéss�s
	if (av == NULL)
		return;  // Sortir de la fonction main si aucun argument n'est disponible

	// Parcourir tous les arguments jusqu'a ce que le pointeur vers le prochain argument soit NULL
	while (av[i] != NULL)
	{
		j = 0;  // Réinitialiser l'indice de caractère pour chaque nouvel argument

		// Parcourir chaque caractère de l'argument actuel jusqua la fin de la chaîne ('\0')
		while (av[i][j] != '\0')
		{
			putchar(av[i][j]);  // Afficher le caractère actuel
			j++;  // Passer au caractère suivant dans le mêmargument
		}
		putchar('\n');  // Ajouter un saut de ligne après avoir afficer� tous les caractères de rgument
		i++;  // Passer a  l'argument suivant
	}
}
void display_usage(char* program_name)
{
	// Afficher un message d'utilisation indiquant comment utiliser le programme
	printf("Usage: %s <command>\n", program_name);
}

void execute_command()
{
	pid_t my_pid;  // PID du processus principal (père)
	pid_t child_pid = 1;  // PID du processus enfant, initialiséa 1 pour entrer dans la boucle au moins une fois
	int i = 0;  // Compteur utilisé pour limiter le nombre de fork
	int status;  // Variable pour stocker le statut du processus enfant termin�
	char* argv[] = { "bin/ls", "-l", "tmp/", NULL };  // Arguments pour la commande a exécuter avec execve()
							 
	// Récupérer le PID du processus principal (père
	my_pid = getpid();
	// Effectuer jusqu'a 4 forks, chacun créant un nouveau processus enfant

	while (i <= 4 && (child_pid != 0))
	{
		child_pid = fork();  // Créer un nouveau processus enfant
		if (child_pid == -1)
		{
			printf("error");  // Afficher un message d'erreur si le fork échoue
			return;  // Quitter le programme avec un code erreur
		}
		wait(&status);  // Attendre la fin du processus enfant créé préc�ment
		i++;  // Incrémenter le compter
	}
	// Si le processus actuel est un enfant
	if (child_pid == 0)
	{
		printf("ID child: %u\n\n ID father: %u\n", getpid(), getppid());  // Afficher les PID de l'enfant et du père
		printf(" \n\n");  // Saut de quelques lignes pour la lisibilit�
	}
	else
	{
		printf("%u I'm your father: %u\n", my_pid, child_pid);  // Afficher le PID du père et celui du dernier enfant c��
	}
	// Exécuter la commande spécifiée dans argv avec execve()
	if (execve(argv[0], argv, NULL) == -1)
		return;  // En cas d'erreur, quitter le programme avec un code de succ�s
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		display_usage(argv[0]);
		return (1);
	}
	else
	{
		display_arguments(argc, argv);
		execute_command();
	}
	return (0);
}

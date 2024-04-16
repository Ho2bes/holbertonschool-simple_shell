#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	printf("Parent process running...\n");
	for (int child_num = 1; child_num <= 5; child_num++)
	{
		pid_t child_pid = fork();

		if (child_pid == -1) 
		{
			perror("Error:");
			return (1);
		}
		else if (child_pid == 0)
		{
			// Child process
			printf("Child process %d running...\n", child_num);
			execlp("ls", "ls", "-l", "/tmp", NULL);
			perror("Error:");
			exit(EXIT_FAILURE);
		}
		else
		{
			// Parent process
			int status;
			wait(&status);
			printf("Child process %d exited with status %d\n", child_num, WEXITSTATUS(status));
		}
	}
	// Parent process
	for (int i = 0; i < 5; i++)
	{
		int status;
		wait(&status);
		printf("Child process %d exited with status %d\n", i+1, WEXITSTATUS(status));
	}
	printf("All child processes have exited.\n");
	return (0);
}

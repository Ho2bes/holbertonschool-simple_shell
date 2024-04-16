#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t my_pid;
	pid_t child_pid = 1;
	int i = 0;
	int status;
	char *argv[] = {"bin/ls", "-l", "tmp/", NULL};

	my_pid = getpid();
	while (i <= 4 && (child_pid != 0))
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			printf("error");
			return (1);
		}
		wait(&status);
		i++;
	}
	if (child_pid == 0)
	{
		printf("ID child: %u\n\n ID father: %u\n", getpid(), getppid());
		printf(" \n\n");
	}
	else
	{
		printf("%u I'm your father: %u\n", my_pid, child_pid);
	}
	if (execve(argv[0], argv, NULL) == -1)

	return (0);
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>


int main(void)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		char *a;
		a = malloc(300);
		exit(0);
	}
	else
		wait(0);
	return (0);
}












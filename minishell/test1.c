#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>


// int	errorsignal;

void	catcher(int signum)
{
	write(1, "hey!\n", 5);
}

int aux(char **env)
{
		pid_t a;
	int stat;
	char **args;
    struct sigaction new_action;
	char *lul;

	a = fork();
	lul = strdup("hi");
	new_action.sa_handler = catcher;
	new_action.sa_flags = 0;
	sigemptyset(&new_action.sa_mask);
	sigaction(SIGINT, &new_action, 0);
	args = calloc(sizeof(char *), 2);
	args[0] = strdup("/usr/bin/cat");
	if (!a)
	{
		execve(args[0], args, env);
	}
	else
	{
		free(args[0]);
		free(args);
		waitpid(a, &stat, 0);
		while (lul)
		{
			free(lul);
			lul = readline("welcome:");
			if (!strncmp(lul, "a", 1))
				break;
		}
		free(lul);
		printf("cleared\n");
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	if (!ac || !av || !env)
		return (0);
	aux(env);
	return (0);
}












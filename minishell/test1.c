#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int	errorsignal;

void	catcher(int signum)
{
	if (signum == SIGINT)
	{
		errorsignal = SIGINT;
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}

int aux(char **env)
{
		pid_t a;
	int stat;
	char **args;
    struct sigaction int_action;
    struct sigaction quit_action;
	char *lul;

	stat = 0;
	a = fork();
	lul = strdup("hi");
	int_action.sa_handler = catcher;
	int_action.sa_flags = 0;
	sigemptyset(&int_action.sa_mask);
	sigaction(SIGINT, &int_action, 0);
	signal(SIGQUIT, SIG_IGN);
	args = calloc(sizeof(char *), 2);
	args[0] = strdup("/usr/bin/cat");
	if (!a)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(args[0], args, env);
	}
	else
	{
		free(args[0]);
		free(args);
		waitpid(a, &stat, 0);
		if (stat == 131)
			write(2, "Quit (core dumped)\n", 20);
		while (lul)
		{
			free(lul);
			lul = readline("welcome:");
			if (!lul)
				break ;
			if (!strcmp(lul, "exit"))
				break;
			add_history(lul);
		}
		free(lul);
		rl_clear_history();
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












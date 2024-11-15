/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:43:13 by snek              #+#    #+#             */
/*   Updated: 2024/11/15 06:59:42 by snek             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

int	g_bigsignal;


static void	catcher(int signum)
{
	static int a;

	if (signum == SIGINT)
	{
		printf("caught %d\n", a++);
		if (a == 2)
			g_bigsignal = SIGINT;
	}
}

static void	catcher_exec(int signum)
{
	if (signum == SIGINT)
	{
		g_bigsignal = SIGINT;
		write(2, "HUH???\n", 7);
	}
}

void    signals(void)
{
    struct sigaction int_action;

    int_action.sa_handler = catcher;
    int_action.sa_flags = 0;
    sigemptyset(&int_action.sa_mask);
	sigaddset(&int_action.sa_mask, SIGINT);
    sigaction(SIGINT, &int_action, 0);
    signal(SIGQUIT, SIG_IGN);
}

int main(void)
{
	int pid;

	g_bigsignal = 0;
	pid = fork();
	if (!pid)
	{
		signals();
		while (g_bigsignal != SIGINT)
			;
		execve("/bin/cat", (char *[]){"/bin/cat", 0}, 0);
	}
	else
	{
		int err;
		int stat;

		err = 0;
		stat = 0;
		printf("WAITING\n");
		signals();
		while ((err == -1 && errno == EINTR) || !err)
			err = waitpid(pid, &stat, 0);
		printf("Done waiting %d\n", err);
		perror("shell");
		signal(SIGINT, SIG_DFL);
	}
	return (0);
}

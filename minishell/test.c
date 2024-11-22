/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snek <snek@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:43:13 by snek              #+#    #+#             */
/*   Updated: 2024/11/22 01:51:46 by snek             ###   ########.fr       */
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
#include "minishell.h"

int	g_bigsignal;

// static char	**dupenv(char **ev)
// {
// 	char	**env;
// 	int		i;

// 	if (!ev)
// 		return (ft_calloc(1, sizeof(char *)));
// 	i = 0;
// 	while (ev[i])
// 		i++;
// 	env = ft_calloc(sizeof(char *), i + 1);
// 	while (i--)
// 		env[i] = ft_strdup(ev[i]);
// 	return (env);
// }

// static t_shell	*fillshell(char **ev)
// {
// 	t_shell	*shell;

// 	shell = ft_calloc(sizeof(t_shell), 1);
// 	if (!shell)
// 		return (0);
// 	shell->env = dupenv(ev);
// 	if (!shell->env)
// 		return (free(shell), NULL);
// 	shell->pipe = 0;
// 	shell->tree = 0;
// 	shell->type = SHELL;
// 	return (shell);
// }

// int main(int ac, char **av, char **ev)
// {

// 	int err = 0; 
// 	t_shell *shell;
// 	char *buff;

// 	buff = strdup("echo a");
// 	if (!ac || !av)
// 		return (333);
// 	shell = fillshell(ev);
// 	err = parsecmd(&shell, buff, err);
// 	arrayfree(&shell->env);
// 	free(shell);
// 	return (err);
// }


int main(void)
{
	// char	*str = strdup('$"HOLA"');
	char	**all = (char *[2]){strdup("$\"HOLA\""), NULL};

	all = args(all, 0);
	int	i = 0;
	while (all[i])
	{
		printf("a%sa\n", all[i]);
		free(all[i]);
		i++;
	}
	free(all);
	return (0);
}
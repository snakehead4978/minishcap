/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jla-chon <jla-chon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:21:26 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/19 17:24:43 by jla-chon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dupenv(char **ev)
{
	char **env;
	int	i;
	
	if (!ev)
		return (calloc(1, sizeof(char *)));
	i = 0;
	while (ev[i])
		i++;
	env = calloc(sizeof(char *), i + 1);
	while (i--)
		env[i] = ft_strdup(ev[i]);
	return (env);
}

static t_shell	*fillshell(char **ev)
{
	t_shell	*shell;
	
	shell = calloc(sizeof(t_shell) , 1);
	if (!shell)
		return (0);
	shell->env = dupenv(ev);
	if (!shell->env)
		return (free(shell), NULL);
	shell->pipe = 0;
	shell->tree = 0;
	shell->type = SHELL;
}

static void	catcher(int signum)
{
	if (signum == SIGINT)
	{
		bigsignal = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	signals(void)
{
	struct sigaction int_action;
    struct sigaction quit_action;

	int_action.sa_handler = catcher;
	int_action.sa_flags = 0;
	sigemptyset(&int_action.sa_mask);
	sigaction(SIGINT, &int_action, 0);
	signal(SIGQUIT, SIG_IGN);
}

static int	checkerr(int err)
{
	if (bigsignal == SIGINT)
	{
		bigsignal = 0;
		return (130);
	}
	return (err);
}

int	main(int ac, char **av, char **ev)
{
	int	err;
	t_shell	*shell;
	char	*buff;

	if (!ac || !av)
		return (1);
	err = 0;
	shell = fillshell(ev);
	signals();
	if (!shell)
		return (1);
	while (1)
	{
		bigsignal = 0;
		buff = readline("minishell:~$");
		if (!buff)
			break ;
		err = checkerr(err);
		parsecmd(&shell, buff);
		err = checkerr(err);
		err = executer(shell, err);
		add_history(buff);
		free(buff);
	}
	arrayfree(shell->env);
	free(shell);
	rl_clear_history();
	return (err);
}

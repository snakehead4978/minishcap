/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:21:26 by jla-chon          #+#    #+#             */
/*   Updated: 2024/11/28 16:54:59 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_bigsignal;

static char	**dupenv(char **ev)
{
	char	**env;
	int		i;

	if (!ev)
		return (ft_calloc(1, sizeof(char *)));
	i = 0;
	while (ev[i])
		i++;
	env = ft_calloc(sizeof(char *), i + 1);
	while (i--)
		env[i] = ft_strdup(ev[i]);
	return (env);
}

static t_shell	*fillshell(char **ev)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (!shell)
		return (0);
	shell->env = dupenv(ev);
	if (!shell->env)
		return (free(shell), NULL);
	shell->pipe = 0;
	shell->tree = 0;
	shell->type = SHELL;
	return (shell);
}

static int	checkerr(int err)
{
	if (g_bigsignal == SIGINT)
	{
		g_bigsignal = 0;
		return (130);
	}
	return (err);
}

static void	init(int *err, t_shell **shell, char **ev)
{
	g_bigsignal = 0;
	*err = 0;
	*shell = fillshell(ev);
	signals();
}

int	main(int ac, char **av, char **ev)
{
	int		err;
	t_shell	*shell;
	char	*buff;

	if (!ac || !av)
		return (333);
	init(&err, &shell, ev);
	if (!shell)
		return (1);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		buff = readline("minishell:~$");
		if (!buff)
			break ;
		err = checkerr(err);
		err = parsecmd(&shell, buff, err);
		err = checkerr(err);
		err = executer(shell, err, buff);
		err = checkerr(err);
		add_history(buff);
		free(buff);
	}
	arrayfree(&shell->env);
	return (free(shell), rl_clear_history(), err);
}

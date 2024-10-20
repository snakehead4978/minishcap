/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:21:26 by jla-chon          #+#    #+#             */
/*   Updated: 2024/10/20 20:23:01 by dakojic          ###   ########.fr       */
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

int	main(int ac, char **av, char **ev)
{
	int err;
	t_shell *shell;
	char *buff;

	if (!ac || !av)
		return (333);
	g_bigsignal = 0;
	err = 0;
	shell = fillshell(ev);
	signals();
	if (!shell)
		return (1);
	while (1)
	{
		g_bigsignal = 0;
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